// RadioMicroscope v2 - palm-sized 5.8 GHz variant for analog FPV video.
// The same model as radiomicroscope.scad with a small circular patch
// antenna, GM2804 motors, an RX5808 receiver on the cradle, an 80 mm base
// and a grip for carrying it.
// Values set after the include replace the defaults.
include <radiomicroscope.scad>

layout = "palm";
handheld = true;   // carried in the hand: grip under the base

// Foxeer Echo 2 patch, 40 x 22 mm (shop figures; thickness ASSUMED)
ant_w = 40;
ant_h = 22;
ant_t = 8;
cam_w = 0;         // no camera strip
deck_gap = 10;     // room for the driver boards on the deck

// iFlight GM2804 with encoder (maker's page)
mot_d = 35;
mot_h = 25;
mot_shaft_od = 8;
mot_bore = 6.5;
mot_enc_d = 26;        // ASSUMED
mot_bolt_circle = 16;  // ASSUMED

base_d = 80;
tub_h = 18;
