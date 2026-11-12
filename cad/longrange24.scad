// RadioMicroscope v2 - long-range 2.4 GHz variant.
// The desk model with a 16 dBi panel antenna in its enclosure and the
// larger GM4108H motors that its weight needs.
include <radiomicroscope.scad>

// AntenaBox v2 16: 194 x 179 x 78 mm, 357 g (shop figures)
ant_w = 194;
ant_h = 179;
ant_t = 78;
ant_off = 39;      // antenna centred on the tilt axis, so its weight balances

// iFlight GM4108H-120T with encoder (maker's page)
mot_d = 47;
mot_h = 32.3;
mot_shaft_od = 10;
mot_bore = 8;
mot_enc_d = 32;        // ASSUMED
mot_bolt_circle = 25;  // ASSUMED

arm_t = 8;
base_d = 160;
