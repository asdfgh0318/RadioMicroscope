#!/usr/bin/env python3
"""Test of tools/locate.py against a synthetic log. Run with `make test`."""
import math
import os
import random
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import locate  # noqa: E402

HEADER = "type,ms,lat,lon,alt_m,sats,nav,heading,pitch,roll,head_az,head_el,world_az,world_el,dbm,frames,channel\n"
TX = (52.2330, 21.0150)   # the transmitter to be found
REF = (52.2300, 21.0100)


def bearing_from(lat, lon):
    e, n = locate.to_local(TX[0], TX[1], lat, lon)
    return math.degrees(math.atan2(e, n)) % 360


def write_log(path, noise_deg, rng):
    spots = [(0, 0), (250, -80), (-120, 300), (400, 350), (60, 520), (-200, -150)]
    with open(path, "w") as f:
        f.write(HEADER)
        for i, (e, n) in enumerate(spots):
            lat, lon = locate.from_local(e, n, *REF)
            b = (bearing_from(lat, lon) + rng.gauss(0, noise_deg)) % 360
            # a few sample rows, which the tool must ignore
            f.write(f"S,{i*1000},{lat:.7f},{lon:.7f},120.0,9,1,10.0,0.0,0.0,0.0,-30.0,{b:.1f},-30.0,-60.0,3,33\n")
            f.write(f"B,{i*1000+500},{lat:.7f},{lon:.7f},120.0,9,1,10.0,0.0,0.0,0.0,-30.0,{b:.1f},-30.0,-58.0,0,33\n")
        f.write("B,9000,,,,0,1,10.0,0.0,0.0,0.0,-30.0,123.0,-30.0,-58.0,0,33\n")   # no GPS fix
        f.write("B,9500,52.2300000,21.0100000,120.0,9,1,0,0,0,0,-30,5.0,-30,-70.0,0,40\n")  # another channel


def check(cond, what):
    if not cond:
        print("  FAIL", what)
        sys.exit(1)


def main():
    rng = random.Random(3)
    with tempfile.TemporaryDirectory() as d:
        exact = os.path.join(d, "exact.csv")
        write_log(exact, 0.0, rng)
        bearings, skipped = locate.read_bearings([exact], channel=33)
        check(len(bearings) == 6 and skipped == 1, "reads 6 bearings, skips the one without GPS")
        lat, lon, rms, behind = locate.solve(bearings)
        e, n = locate.to_local(lat, lon, *TX)
        check(math.hypot(e, n) < 3 and behind == 0, f"exact bearings land on the transmitter ({math.hypot(e, n):.1f} m)")

        noisy = os.path.join(d, "noisy.csv")
        write_log(noisy, 5.0, rng)
        lat, lon, rms, behind = locate.solve(locate.read_bearings([noisy], channel=33)[0])
        e, n = locate.to_local(lat, lon, *TX)
        miss = math.hypot(e, n)
        print(f"  6 bearings with 5 deg noise: {miss:.0f} m from the truth at about 500 m range")
        check(miss < 80, "noisy bearings land near the transmitter")

        # Parallel bearings must be refused.
        check(locate.solve([(52.23, 21.01, 45.0, -60), (52.231, 21.0116, 45.2, -60)]) is None, "parallel bearings refused")

        # The command line runs end to end and writes GeoJSON.
        out = os.path.join(d, "out.json")
        run = subprocess.run([sys.executable, os.path.join(ROOT, "tools", "locate.py"), noisy, "--channel", "33",
                              "--geojson", out], capture_output=True, text=True)
        check(run.returncode == 0 and "transmitter near" in run.stdout and os.path.getsize(out) > 200, "command line run")
    print("locate.py: all checks passed")


if __name__ == "__main__":
    main()
