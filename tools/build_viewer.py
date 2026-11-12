#!/usr/bin/env python3
"""Build the interactive 3D view of the head (build/model.html) and the
printable parts (cad/stl/*.stl).

Exports every colour of every moving frame of cad/radiomicroscope.scad with
OpenSCAD and packs the triangles into the page template
cad/viewer_template.html.

Usage: tools/build_viewer.py [variant]   (needs openscad on PATH)
Variants are listed in cad/variants.json; the default is "desk".
"""
import base64
import json
import pathlib
import re
import struct
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
OUT = ROOT / "build"
VARIANTS = json.loads((ROOT / "cad" / "variants.json").read_text())
VARIANT = VARIANTS[sys.argv[1] if len(sys.argv) > 1 else "desk"]
SCAD = ROOT / VARIANT["scad"]

FRAMES = ["static", "yoke", "cradle"]
COLOURS = ["print", "motor", "rotor", "pcb", "pcbdark", "pcbblue", "metal", "antenna", "cable"]
DIM_KEYS = ["base_h", "mot_h", "tilt_z", "width", "ant_w", "ant_h", "ant_t", "base_d",
            "deck_z", "tilt_above_deck", "height", "grip", "ant_off"]
PRINTED = ["p_tub", "p_lid", "p_yoke", "p_cradle"]


def export(part: str, only: str = ""):
    """Returns (triangle floats, dims or None) for one part, optionally one colour of it."""
    stl = OUT / f"_{part}_{only}.stl"
    run = subprocess.run(
        ["openscad", "-D", f'part="{part}"', "-D", f'only="{only}"', "-D", "$fn=40", "-o", str(stl), str(SCAD)],
        capture_output=True, text=True, timeout=600)
    dims = None
    m = re.search(r"dims = \[([^\]]+)\]", run.stderr + run.stdout)
    if m:
        dims = [float(x) for x in m.group(1).split(",")]
    if not stl.exists():
        if "empty" in (run.stderr + run.stdout).lower():
            return [], dims          # this frame has nothing in that colour
        sys.exit(f"openscad failed for {part} {only}:\n{run.stderr}")
    verts = [float(v) for line in stl.read_text().splitlines() if line.strip().startswith("vertex")
             for v in line.split()[1:4]]
    stl.unlink()
    return verts, dims


def main() -> None:
    OUT.mkdir(exist_ok=True)
    meshes, dims, triangles = [], None, 0
    for frame in FRAMES:
        for colour in COLOURS:
            verts, d = export(f"f_{frame}", colour)
            dims = dims or d
            if not verts:
                continue
            triangles += len(verts) // 9
            packed = base64.b64encode(struct.pack(f"<{len(verts)}f", *verts)).decode()
            meshes.append({"frame": frame, "colour": colour, "data": packed})
    if not dims:
        sys.exit("the model did not report its dimensions (echo(dims=...))")
    page = (ROOT / "cad" / "viewer_template.html").read_text()
    page = page.replace("/*MESHES*/[]", json.dumps(meshes))
    page = page.replace("/*DIMS*/{}", json.dumps(dict(zip(DIM_KEYS, dims))))
    page = page.replace("/*META*/{}", json.dumps({"legend": VARIANT["legend"], "notes": VARIANT["notes"]}))
    for key in ("title", "heading", "lede"):
        page = page.replace("{{" + key.upper() + "}}", VARIANT[key])
    (ROOT / VARIANT["out"]).write_text(page)
    print(f"{VARIANT['out']}: {len(meshes)} meshes, {triangles} triangles, {len(page) // 1024} kB")
    print("dimensions:", dict(zip(DIM_KEYS, dims)))

    # Printable parts, in print orientation.
    stl_dir = ROOT / VARIANT["stl"]
    stl_dir.mkdir(exist_ok=True)
    for part in PRINTED + VARIANT.get("extra_parts", []):
        out = stl_dir / f"{part[2:]}.stl"
        run = subprocess.run(["openscad", "-q", "-D", f'part="{part}"', "-o", str(out), str(SCAD)],
                             capture_output=True, text=True, timeout=900)
        if run.returncode != 0:
            sys.exit(f"openscad failed for {part}:\n{run.stderr}")
        print(f"{VARIANT['stl']}/{out.name}: {out.stat().st_size // 1024} kB")


if __name__ == "__main__":
    main()
