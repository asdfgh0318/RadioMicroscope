# SatNOGS Rotator Controller

Electronics designs for [SatNOGS Rotator](https://gitlab.com/librespacefoundation/satnogs/satnogs-rotator).

Repository includes all source files of PCB's for the SatNOGS rotator controller assembly.

Firmware can be found on [satnogs-rotator-firmware](https://gitlab.com/librespacefoundation/satnogs/satnogs-rotator-firmware).

Stable versions are tagging with x.y name.

## Documentation

More information can be found in our [wiki](https://wiki.satnogs.org/SatNOGS_Rotator_Controller).

## Contribute
This is a KiCAD project thus merging can be tricky.
Coordinate with project engineers before starting any changes and take look at issues.

#### EDA
KiCAD 5.1
Requires [lsf-kicad-lib](https://gitlab.com/librespacefoundation/lsf-kicad-lib) to be installed.

#### Schematic
Changes in manufacturer part numbers field, footprints and designators can be merged most of the times.
Any part change, change in placement, wire placement etc cannot be merged at this point.

One exception is Hierarchical sheets provided that:

* A single person is working on a Hierarchical sheet
* Annotation is using sheet number
* Global nets are respected
* Changes in Hierarchical labels are coordinated

#### PCB
At this point any merging on PCB files must be avoided.

## License

&copy; [![Libre Space Foundation](https://img.shields.io/badge/%C2%A9%202014--2020-Libre%20Space%20Foundation-6672D8.svg)](https://librespacefoundation.org/).

Licensed under the [CERN OHLv1.2](LICENSE).
