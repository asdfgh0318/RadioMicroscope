#!/usr/bin/env python3
"""Locate a transmitter from RadioMicroscope log files.

Reads the CSV files written to the microSD card (firmware/brain/log_sd.h),
takes the bearing rows ("B": the strongest direction found by one turn
scan, with the GPS position it was taken from), and finds the point closest
to all the bearing lines. The method is the same least-squares fit as
lib/RMCore/src/rm_locate.h.

Usage: tools/locate.py LOG.csv [LOG.csv ...] [--channel N] [--geojson OUT.json]

A fix needs at least two bearings taken from clearly different places.
Signal strength is not used as a distance: it only weights the bearings.
"""
import argparse
import csv
import json
import math
import sys

EARTH = 6371000.0


def to_local(lat, lon, lat0, lon0):
    """Metres east and north of the reference point."""
    north = math.radians(lat - lat0) * EARTH
    east = math.radians(lon - lon0) * EARTH * math.cos(math.radians(lat0))
    return east, north


def from_local(east, north, lat0, lon0):
    lat = lat0 + math.degrees(north / EARTH)
    lon = lon0 + math.degrees(east / (EARTH * math.cos(math.radians(lat0))))
    return lat, lon


def read_bearings(paths, channel=None):
    """Returns [(lat, lon, bearing_deg, dbm)] from the B rows that have a GPS position."""
    out, skipped = [], 0
    for path in paths:
        with open(path, newline="") as f:
            for row in csv.DictReader(f):
                if row.get("type") != "B":
                    continue
                if channel is not None and row.get("channel") != str(channel):
                    continue
                try:
                    out.append((float(row["lat"]), float(row["lon"]), float(row["world_az"]), float(row["dbm"])))
                except (ValueError, KeyError):
                    skipped += 1  # no GPS fix when the bearing was taken
    return out, skipped


def solve(bearings):
    """Least-squares crossing of bearing lines.

    Returns (lat, lon, rms_m, behind), or None when the lines are too close
    to parallel. rms_m is the typical miss distance of the lines from the
    result; behind counts bearings that point away from it.
    """
    lat0 = sum(b[0] for b in bearings) / len(bearings)
    lon0 = sum(b[1] for b in bearings) / len(bearings)
    strongest = max(b[3] for b in bearings)
    sxx = sxy = syy = bx = by = 0.0
    lines = []
    for lat, lon, bearing, dbm in bearings:
        e, n = to_local(lat, lon, lat0, lon0)
        b = math.radians(bearing)
        nx, ny = math.cos(b), -math.sin(b)       # unit normal of the bearing line
        w = 10 ** ((dbm - strongest) / 20.0)     # stronger sightings count for more
        d = nx * e + ny * n
        sxx += w * nx * nx
        sxy += w * nx * ny
        syy += w * ny * ny
        bx += w * nx * d
        by += w * ny * d
        lines.append((e, n, b))
    det = sxx * syy - sxy * sxy
    if det < 0.01 * (sxx + syy) ** 2:
        return None
    east = (syy * bx - sxy * by) / det
    north = (sxx * by - sxy * bx) / det
    miss2, behind = 0.0, 0
    for e, n, b in lines:
        de, dn = east - e, north - n
        miss2 += (math.cos(b) * de - math.sin(b) * dn) ** 2
        if math.sin(b) * de + math.cos(b) * dn < 0:
            behind += 1
    lat, lon = from_local(east, north, lat0, lon0)
    return lat, lon, math.sqrt(miss2 / len(lines)), behind


def geojson(bearings, result, length_m=2000.0):
    feats = []
    for lat, lon, bearing, dbm in bearings:
        b = math.radians(bearing)
        end = from_local(length_m * math.sin(b), length_m * math.cos(b), lat, lon)
        feats.append({"type": "Feature", "properties": {"kind": "bearing", "bearing": bearing, "dbm": dbm},
                      "geometry": {"type": "LineString", "coordinates": [[lon, lat], [end[1], end[0]]]}})
    if result:
        feats.append({"type": "Feature", "properties": {"kind": "transmitter", "rms_m": round(result[2], 1)},
                      "geometry": {"type": "Point", "coordinates": [result[1], result[0]]}})
    return {"type": "FeatureCollection", "features": feats}


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("logs", nargs="+")
    ap.add_argument("--channel", type=int, help="use only bearings taken on this channel")
    ap.add_argument("--geojson", help="write bearing lines and the result as GeoJSON")
    args = ap.parse_args()

    bearings, skipped = read_bearings(args.logs, args.channel)
    print(f"{len(bearings)} bearings with a GPS position" + (f", {skipped} without (ignored)" if skipped else ""))
    if len(bearings) < 2:
        print("Need at least two bearings from different places.")
        return 1
    result = solve(bearings)
    if args.geojson:
        with open(args.geojson, "w") as f:
            json.dump(geojson(bearings, result), f)
        print(f"wrote {args.geojson}")
    if result is None:
        print("The bearings are nearly parallel: take more from positions off to one side.")
        return 1
    lat, lon, rms, behind = result
    print(f"transmitter near {lat:.6f}, {lon:.6f}")
    print(f"bearing lines miss that point by {rms:.0f} m RMS")
    if behind:
        print(f"warning: {behind} bearing(s) point away from it (reflection or a wrong peak?)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
