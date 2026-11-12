// RadioMicroscope v2 - head assembly (brushless drivetrain, compact fork)
//
// Units: mm. Z is up, the pan axis is the Z axis, the tilt axis is parallel
// to X, and the antenna looks along +Y when az = 0 and el = 0.
//
//   part = "assembly"                       everything, posed by az / el
//   part = "p_tub" | "p_lid" | "p_yoke" | "p_cradle"
//                                           one printed part, in print orientation
//   part = "f_static" | "f_yoke" | "f_cradle", only = "<colour>"
//                                           one colour of one moving frame
//                                           (used by tools/build_viewer.py)
//
// Bought components are drawn from their published overall dimensions.
// Dimensions marked ASSUMED were not found in a datasheet: measure the real
// part before printing.

part = "assembly";
only = "";   // colour filter; "" shows everything
az = 25;     // pan angle shown, degrees
el = 30;     // tilt angle shown, degrees

// ---- antenna: 2.4 GHz 9 dBi patch, 90 x 80 x 10 mm ----------------------
ant_w = 90;
ant_h = 80;
ant_t = 10;
ant_off = 0;   // how far the antenna's rear face sits behind the tilt axis; half its
               // depth puts a deep, heavy antenna in balance

// ---- gimbal motor: iFlight GM3506 with encoder ----------------------------
mot_d = 40;            // outer diameter
mot_h = 25.8;          // height including the encoder housing
mot_shaft_od = 12;     // hollow shaft
mot_bore = 8.6;
mot_enc_h = 5.8;       // ASSUMED split of the height: encoder housing
mot_enc_d = 30;        // ASSUMED
mot_bolt_circle = 19;  // ASSUMED mounting pattern, 4 x M3
mot_bolt_d = 3.2;

// ---- printed structure ----------------------------------------------------
wall = 4;
arm_t = 6;             // fork arm thickness
deck_t = 5;
clear = 6;             // gap around the swinging cradle
base_d = 120;
tub_h = 24;
lid_t = 4;
base_h = tub_h + lid_t;
cam_w = 22;            // strip beside the antenna for the camera board
deck_gap = 0;          // extra height under the cradle, for boards lying on the deck

// ---- layout ---------------------------------------------------------------
// "desk": sensor radio and camera brain ride on the cradle, motor controller
//         and drivers on the left arm.
// "palm": an RX5808 video receiver rides on the cradle; the brain and the
//         drivers lie on the deck and the motor controller on the left arm.
layout = "desk";

// A grip under the base, for carrying the head in the hand. It screws to
// the base's tripod thread and carries the compass and IMU at its far end,
// well away from the motor magnets.
handheld = false;
grip_len = 115;
grip_d = 34;

cradle_w = ant_w + cam_w;                     // plate width
side_x = cradle_w/2;                          // inner face of the cradle side plates
swing = sqrt(pow(ant_h/2, 2) + pow(max(ant_t - ant_off + 6, ant_off > 0 ? ant_off + wall + 12 : 0), 2)) + clear;   // radius swept by the cradle
tilt_h = swing + 2 + deck_gap;                // tilt axis above the deck top
right_arm_x = side_x + wall + mot_h - mot_enc_h;  // inner face of the motor arm (encoder housing sits in the arm)
left_arm_x = -(side_x + wall + 2);            // inner face of the pivot arm
fork_mid = (right_arm_x + arm_t + left_arm_x - arm_t) / 2;
xs = -fork_mid;                               // shift that puts the pan axis mid-fork
deck_y = 30;                                  // deck half-depth
deck_z = base_h + mot_h - mot_enc_h;          // deck underside above the table (encoder housing sits in the deck)
tilt_z = deck_z + deck_t + tilt_h;            // tilt axis above the table

$fn = 72;

function pal(n) =
    n == "print"   ? [0.84, 0.85, 0.82] :
    n == "motor"   ? [0.16, 0.17, 0.20] :
    n == "rotor"   ? [0.30, 0.33, 0.40] :
    n == "pcb"     ? [0.10, 0.42, 0.30] :
    n == "pcbdark" ? [0.12, 0.13, 0.16] :
    n == "pcbblue" ? [0.14, 0.20, 0.55] :
    n == "metal"   ? [0.72, 0.74, 0.77] :
    n == "antenna" ? [0.95, 0.96, 0.97] :
    n == "cable"   ? [0.78, 0.55, 0.12] : [1, 0, 1];

module col(n) { if (only == "" || only == n) color(pal(n)) children(); }

module bolt_circle(h, d = mot_bolt_d) {
    for (a = [45, 135, 225, 315]) rotate(a) translate([mot_bolt_circle/2, 0, -1]) cylinder(d = d, h = h + 2);
}

// ===========================================================================
// Bought parts
// ===========================================================================

// Gimbal motor, axis along Z. Stator half: z 0 .. mot_h/2 with the encoder
// housing below it; rotor half above. Drawn as two bodies because they sit
// in different moving frames.
mot_stator_h = (mot_h - mot_enc_h) * 0.45;
mot_rotor_h = mot_h - mot_enc_h - mot_stator_h;

module motor_stator() {
    col("motor") difference() {
        union() {
            cylinder(d = mot_enc_d, h = mot_enc_h);                                   // encoder housing
            translate([0, 0, mot_enc_h]) cylinder(d = mot_d - 2, h = mot_stator_h);   // stator base
        }
        translate([0, 0, -1]) cylinder(d = mot_bore, h = mot_h);
    }
    col("cable") translate([mot_enc_d/2 - 2, -4, 1]) cube([10, 8, 2.5]);              // wire exit
}

module motor_rotor() {
    translate([0, 0, mot_enc_h + mot_stator_h]) {
        col("rotor") difference() {
            union() {
                translate([0, 0, 0.6]) cylinder(d = mot_d, h = mot_rotor_h - 2.6);
                translate([0, 0, mot_rotor_h - 2]) cylinder(d1 = mot_d, d2 = mot_d - 5, h = 2);
            }
            translate([0, 0, -1]) cylinder(d = mot_shaft_od, h = mot_rotor_h + 2);
            translate([0, 0, mot_rotor_h - 1.5]) bolt_circle(3, 2.6);
            for (a = [0 : 60 : 300]) rotate(a) translate([mot_d/2 - 6, 0, mot_rotor_h - 1]) cylinder(d = 5, h = 3);
        }
        col("metal") difference() {
            cylinder(d = mot_shaft_od, h = mot_rotor_h);
            translate([0, 0, -1]) cylinder(d = mot_bore, h = mot_rotor_h + 2);
        }
    }
}

module motor() { motor_stator(); motor_rotor(); }

// Seeed XIAO (21 x 17.8 mm). camera = true adds the Sense board and camera.
module xiao(camera = false) {
    col("pcbdark") translate([-10.5, -8.9, 0]) cube([21, 17.8, 1.2]);
    col("metal") translate([-4, -6, 1.2]) cube([12.5, 12, 2.4]);                       // radio shield
    col("metal") translate([-12, -4.5, 1.2]) cube([7.4, 9, 3.2]);                      // USB-C
    if (camera) {
        col("pcbdark") translate([-10.5, -8.9, 4.4]) cube([21, 17.8, 1.2]);            // Sense board
        col("motor") translate([-4.25, -4.25, 5.6]) cube([8.5, 8.5, 4]);               // camera module
        col("motor") translate([0, 0, 9.6]) cylinder(d = 7, h = 2.5);                  // lens
    }
}

// ESP32 board with ESP-WROOM-32, 38 pins, USB-C: 54.6 x 25 x 8 mm (shop figures).
module esp32_devkit() {
    col("pcbdark") translate([-27.3, -12.5, 0]) cube([54.6, 25, 1.6]);
    col("metal") translate([-24.5, -8, 1.6]) cube([18, 16, 3.2]);                      // module shield
    col("pcb") translate([-27.3, -9, 1.6]) cube([3, 18, 0.8]);                         // antenna area
    col("metal") translate([20.3, -4.5, 1.6]) cube([7, 9, 3.2]);                       // USB-C
    for (y = [-11.5, 11.5 - 2.5]) col("motor") translate([-24, y, -8.5]) cube([48, 2.5, 8.5]);  // pin headers
}

// SimpleFOC Mini driver (ASSUMED outline 26 x 21 mm).
module foc_mini() {
    col("pcbblue") translate([-13, -10.5, 0]) cube([26, 21, 1.6]);
    col("motor") translate([-3, -3, 1.6]) cube([6, 6, 1.2]);                           // DRV8313
    col("pcb") translate([6, -7.5, 1.6]) cube([7, 15, 8]);                             // motor terminal
    col("motor") translate([-13, -9, 1.6]) cube([2.5, 18, 6]);                         // signal header
}

// USB-C PD trigger board, 31 x 20 mm (shop listing).
module pd_trigger() {
    col("pcbdark") translate([-15.5, -10, 0]) cube([31, 20, 1.6]);
    col("metal") translate([-16.5, -4.5, 1.6]) cube([7.4, 9, 3.2]);
    col("pcbblue") translate([2, -7, 1.6]) cube([10, 5, 4]);                           // voltage switch
}

// 5 V step-down converter (ASSUMED outline 22 x 17 mm).
module buck() {
    col("pcbblue") translate([-11, -8.5, 0]) cube([22, 17, 1.6]);
    col("motor") translate([-3, -3, 1.6]) cube([7, 7, 3]);                             // inductor
}

// RX5808 analog video receiver module, 28 x 23 x 3 mm (vendor figures).
module rx5808() {
    col("pcb") translate([-14, -11.5, 0]) cube([28, 23, 1]);
    col("metal") translate([-12.5, -10, 1]) cube([25, 20, 2]);     // shield can
}

// Patch antenna, rear face on the plane y = 0, looking along +Y, with its
// SMA connector and a pigtail to the radio.
module antenna() {
    col("antenna") translate([-ant_w/2, 0, -ant_h/2]) cube([ant_w, ant_t, ant_h]);
    col("metal") rotate([90, 0, 0]) cylinder(d = 6.4, h = 12);                          // SMA jack
    col("cable") hull() {
        translate([0, -12, 0]) sphere(d = 1.6);
        translate([layout == "desk" ? -22 : 0, layout == "desk" ? -9 : -16, layout == "desk" ? 8 : 0]) sphere(d = 1.6);
    }
}

// ===========================================================================
// Printed parts
// ===========================================================================

// Base tub: holds the USB-C power input. Prints open side up, no supports.
module tub() {
    col("print") difference() {
        cylinder(d = base_d, h = tub_h);
        translate([0, 0, wall - 1]) cylinder(d = base_d - 2*wall, h = tub_h);            // cavity
        translate([0, 0, -1]) cylinder(d = 6.6, h = wall + 2);                           // 1/4" tripod screw
        translate([0, 0, 1.5]) cylinder(d = 13, h = wall, $fn = 6);                      // nut trap
        translate([0, -base_d/2, wall + 3.5]) cube([10.5, 3*wall, 4.5], center = true);  // USB-C opening
    }
    // screw posts for the lid
    col("print") for (a = [30 : 90 : 300]) rotate(a) translate([base_d/2 - wall - 4, 0, 0]) difference() {
        cylinder(d = 8, h = tub_h);
        translate([0, 0, tub_h - 10]) cylinder(d = 2.6, h = 11);
    }
}

// Lid: carries the pan motor. Prints flat.
module lid() {
    col("print") translate([0, 0, tub_h]) difference() {
        union() {
            cylinder(d = base_d, h = lid_t);
            translate([0, 0, -2]) difference() {                                         // locating lip
                cylinder(d = base_d - 2*wall - 0.4, h = 2);
                translate([0, 0, -1]) cylinder(d = base_d - 2*wall - 4, h = 4);
            }
        }
        translate([0, 0, -3]) cylinder(d = mot_bore + 1, h = lid_t + 4);                 // power wires
        bolt_circle(lid_t, 2.8);                                                         // rotor screws
        for (a = [30 : 90 : 300]) rotate(a) translate([base_d/2 - wall - 4, 0, -1]) cylinder(d = 3.2, h = lid_t + 2);
    }
}

// Fork arm: a plate with flanges on both edges (a C-channel) so that it is
// stiff although it prints standing up. inner = +1 puts the flanges on the
// +X side of the plate, -1 on the -X side.
module arm(x0, flange_dir, hole_d) {
    top = deck_t + tilt_h;
    difference() {
        union() {
            hull() {
                translate([x0, -deck_y, 0]) cube([arm_t, 2*deck_y, deck_t]);
                translate([x0, 0, top]) rotate([0, 90, 0]) cylinder(d = mot_d + 8, h = arm_t);
            }
            for (y = [-deck_y, deck_y - wall]) hull() {                                   // flanges
                translate([x0 + (flange_dir > 0 ? arm_t : -10), y, 0]) cube([10, wall, deck_t]);
                translate([x0 + (flange_dir > 0 ? arm_t : -4), y + (y < 0 ? 4 : -4), top - 10]) cube([4, wall, 1]);
            }
        }
        translate([x0 - 1, 0, top]) rotate([0, 90, 0]) cylinder(d = hole_d, h = arm_t + 2);
    }
}

// Yoke: deck on the pan motor and two fork arms. Prints on its deck.
// Local frame: origin on the pan axis at the deck underside.
module yoke() {
    col("print") translate([xs, 0, 0]) difference() {
        union() {
            translate([left_arm_x - arm_t, -deck_y, 0]) cube([right_arm_x - left_arm_x + 2*arm_t, 2*deck_y, deck_t]);
            arm(right_arm_x, 1, mot_enc_d + 0.6);       // motor arm: encoder housing passes through
            arm(left_arm_x - arm_t, -1, 4.3);           // pivot arm: M4 pivot screw
        }
        // pan motor seat: encoder housing recess, shaft hole, screws
        translate([-xs, 0, 0]) {
            translate([0, 0, -1]) cylinder(d = mot_enc_d + 0.6, h = deck_t + 2);
            bolt_circle(deck_t);
        }
        // tilt motor screws
        translate([right_arm_x, 0, deck_t + tilt_h]) rotate([0, 90, 0]) bolt_circle(arm_t);
        // cable pass-through to the left arm
        translate([left_arm_x + 6, 0, -1]) cylinder(d = 8, h = deck_t + 2);
    }
}

// Cradle: turns with the tilt motor, carries antenna, radio and brain.
// Local frame: origin on the tilt axis, mid-fork; +Y is boresight.
ant_x = cam_w/2;                 // antenna centre
cam_x = -cradle_w/2 + cam_w/2;   // camera strip centre

module cradle() {
    col("print") translate([xs, 0, 0]) difference() {
        union() {
            // back plate; the antenna's rear face sits on its front
            translate([-side_x, -ant_off - wall, -ant_h/2]) cube([cradle_w, wall, ant_h]);
            // side plates: right one bolts to the tilt motor, left one pivots
            for (x = [side_x, -side_x - wall]) hull() {
                translate([x, 0, 0]) rotate([0, 90, 0]) cylinder(d = mot_d - 2, h = wall);
                translate([x, -ant_off - wall, -ant_h/2 + 6]) cube([wall, wall, ant_h - 12]);
            }
            // corner clips for the antenna
            for (z = [-ant_h/2 - 2, ant_h/2]) for (x = [ant_x - ant_w/2, ant_x + ant_w/2 - 14])
                translate([x, -ant_off - wall, z]) cube([14, min(ant_t/2, 12) + wall, 2]);
        }
        translate([side_x, 0, 0]) rotate([0, 90, 0]) { bolt_circle(wall, 2.8); translate([0, 0, -1]) cylinder(d = mot_shaft_od + 0.6, h = wall + 2); }
        translate([-side_x - wall - 1, 0, 0]) rotate([0, 90, 0]) cylinder(d = 3.4, h = wall + 2);       // pivot screw thread
        translate([0, -ant_off, 0]) {
            translate([ant_x, 1, 0]) rotate([90, 0, 0]) cylinder(d = 12, h = wall + 2);                 // antenna connector
            if (layout == "desk") {
                translate([cam_x, 1, 0]) rotate([90, 0, 0]) cylinder(d = 9, h = wall + 2);              // camera lens
                for (z = [-ant_h/2 + 8, ant_h/2 - 8]) translate([cam_x, 1, z]) rotate([90, 0, 0]) cylinder(d = 3.2, h = wall + 2);  // trim weight screws
            }
        }
    }
}

// Grip: prints standing on its top flange. A 1/4" screw passes up through
// the flange into the base; the cable to the power bank runs down the
// centre and out at the bottom.
module grip() {
    col("print") translate([0, 0, -grip_len]) difference() {
        union() {
            cylinder(d = grip_d, h = grip_len - 14);
            translate([0, 0, grip_len - 14]) cylinder(d1 = grip_d, d2 = base_d * 0.7, h = 10);   // flare
            translate([0, 0, grip_len - 4]) cylinder(d = base_d * 0.7, h = 4);                    // flange
            for (z = [18 : 14 : grip_len - 36]) translate([0, 0, z]) cylinder(d = grip_d + 3, h = 5);  // finger ribs
            translate([-11, -grip_d/2 - 3, 0]) cube([22, 4, 24]);                                 // sensor pad
        }
        translate([0, 0, -1]) cylinder(d = grip_d - 8, h = grip_len - 12);                        // cable channel
        translate([0, 0, grip_len - 13]) cylinder(d = 6.6, h = 20);                               // 1/4" screw
        translate([0, grip_d/2 - 2, 8]) rotate([-90, 0, 0]) cylinder(d = 9, h = 8);               // cable exit
    }
}

// Compass and IMU boards on the grip's sensor pad (outlines ASSUMED).
module nav_boards() {
    translate([0, -grip_d/2 - 3.2, -grip_len + 12]) rotate([90, 0, 0]) {
        col("pcbblue") translate([-10, -8, 0]) cube([20, 16, 1.2]);
        col("motor") translate([-2, -2, 1.2]) cube([4, 4, 1]);
    }
}

// ===========================================================================
// Frames: what moves together
// ===========================================================================

module frame_static() {
    tub();
    lid();
    if (handheld) { grip(); nav_boards(); }
    translate([0, -base_d/2 + wall + 16, wall]) rotate(90) pd_trigger();
    // pan motor upside down: its rotor is screwed to the lid and stays still
    translate([0, 0, base_h + mot_h]) rotate([180, 0, 0]) motor_rotor();
}

// Origin: pan axis at the deck underside.
module frame_yoke() {
    yoke();
    translate([0, 0, mot_enc_h]) rotate([180, 0, 0]) motor_stator();                      // pan motor stator, encoder housing up in the deck
    translate([xs, 0, 0]) {
        // tilt motor stator on the right arm, encoder housing through the arm
        translate([right_arm_x + mot_enc_h, 0, deck_t + tilt_h]) rotate([0, -90, 0]) motor_stator();
        // motor controller on the outside of the left arm
        translate([left_arm_x - arm_t, 0, 0])
            translate([-2.4, 0, deck_t + 16]) rotate([0, -90, 0]) rotate(90) esp32_devkit();
        if (layout == "desk") {
            translate([left_arm_x - arm_t, 0, 0]) {
                translate([-0.4, -13.5, deck_t + 46]) rotate([0, -90, 0]) rotate(90) foc_mini();
                translate([-0.4, 13.5, deck_t + 46]) rotate([0, -90, 0]) rotate(90) foc_mini();
            }
            translate([left_arm_x + 22, 14, deck_t]) buck();
        } else {
            // drivers, brain and converter lie on the deck under the cradle
            translate([-xs - 15, 0, deck_t]) rotate(90) foc_mini();
            translate([-xs + 15, 0, deck_t]) rotate(90) foc_mini();
            translate([right_arm_x - 14, 0, deck_t]) rotate(90) xiao();
            translate([left_arm_x + 13, 0, deck_t]) rotate(90) buck();
        }
    }
}

// Origin: pan axis at the height of the tilt axis.
module frame_cradle() {
    cradle();
    translate([xs, 0, 0]) translate([right_arm_x + mot_enc_h, 0, 0]) rotate([0, -90, 0]) motor_rotor();   // tilt motor rotor
    translate([xs, -ant_off, 0]) {
        translate([ant_x, 0, 0]) antenna();
        if (layout == "desk") {
            // sensor radio behind the plate, next to the antenna connector
            translate([ant_x - 26, -wall, 8]) rotate([90, 0, 0]) xiao();
            // brain with camera looking forward through the plate
            translate([cam_x, -wall - 12.1, 0]) rotate([-90, 0, 0]) xiao(camera = true);
        } else {
            // video receiver behind the plate, beside the antenna connector
            translate([ant_x, -wall - 13, 0]) rotate([90, 0, 0]) rx5808();
        }
    }
    col("metal") translate([xs - side_x - wall - 8, 0, 0]) rotate([0, 90, 0]) cylinder(d = 4, h = 12);  // pivot screw
}

module assembly() {
    frame_static();
    rotate(-az) translate([0, 0, deck_z]) {
        frame_yoke();
        translate([0, 0, deck_t + tilt_h]) rotate([el, 0, 0]) frame_cradle();
    }
}

// Dimensions for the viewer and the docs.
echo(dims = [base_h, mot_h, tilt_z, right_arm_x - left_arm_x + 2*arm_t, ant_w, ant_h, ant_t, base_d,
             deck_z, deck_t + tilt_h, tilt_z + max(ant_h/2, mot_d/2 + 4), handheld ? grip_len : 0, ant_off]);

if (part == "assembly") assembly();
if (part == "f_static") frame_static();
if (part == "f_yoke") frame_yoke();
if (part == "f_cradle") frame_cradle();
if (part == "p_tub") tub();
if (part == "p_lid") translate([0, 0, base_h]) rotate([180, 0, 0]) lid();
if (part == "p_yoke") yoke();
if (part == "p_cradle") rotate([90, 0, 0]) cradle();
if (part == "p_grip") rotate([180, 0, 0]) grip();
