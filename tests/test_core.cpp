// Host tests for RMCore. Build and run with `make test`.
//
// The scan and tracking tests run against a simulated antenna: a source at
// a known direction, a main lobe of the given half-power beamwidth, side
// lobes 20 dB down and Gaussian measurement noise.
#include <cstdio>
#include <cstdlib>
#include <random>

#include "RMCore.h"

using namespace rm;

static int g_failed = 0;
static int g_checks = 0;

#define CHECK(cond)                                                    \
    do {                                                               \
        g_checks++;                                                    \
        if (!(cond)) {                                                 \
            g_failed++;                                                \
            printf("  FAIL %s:%d  %s\n", __FILE__, __LINE__, #cond);   \
        }                                                              \
    } while (0)

#define CHECK_NEAR(a, b, tol) CHECK(fabs((double)(a) - (double)(b)) <= (tol))

struct Sky {
    AzEl source{40, 25};
    float peakDbm = -55;
    float hpbw = 40;      // half-power beamwidth, degrees
    float noiseDb = 2;
    bool present = true;
    std::mt19937 rng{12345};

    // Returns false when the source cannot be heard in that direction.
    bool measure(AzEl at, float& dbm) {
        if (!present) return false;
        float sep = separation(at, source);
        float lobe = -12.0f * (sep / hpbw) * (sep / hpbw);  // -3 dB at hpbw/2
        if (lobe < -20) lobe = -20;
        std::normal_distribution<float> n(0, noiseDb);
        dbm = peakDbm + lobe + n(rng);
        return dbm > -95;
    }
};

static void testGeometry() {
    printf("geometry\n");
    CHECK_NEAR(wrap180(190), -170, 1e-3);
    CHECK_NEAR(wrap180(-190), 170, 1e-3);
    CHECK_NEAR(wrap180(180), -180, 1e-3);
    CHECK_NEAR(wrap360(-10), 350, 1e-3);
    CHECK_NEAR(separation({0, 0}, {90, 0}), 90, 1e-2);
    CHECK_NEAR(separation({10, 90}, {200, 90}), 0, 0.1);
    CHECK_NEAR(separation({170, 0}, {-170, 0}), 20, 1e-2);

    Axis a;
    CHECK(a.toCounts(0) == 2048);
    CHECK(a.toCounts(90) == 3072);
    CHECK(a.toCounts(-90) == 1024);
    CHECK(a.toCounts(500) == a.toCounts(178));  // clamped to the limit
    CHECK_NEAR(a.toDeg(a.toCounts(33.3f)), 33.3, 0.05);
    a.dir = -1;
    CHECK(a.toCounts(90) == 1024);
    CHECK_NEAR(a.toDeg(1024), 90, 1e-3);
}

static void testStats() {
    printf("stats\n");
    RssiWindow w;
    w.clear();
    CHECK(w.count() == 0);
    CHECK(w.median() == RssiWindow::kMin);
    for (int v : {-60, -61, -59, -90, -60}) w.add(v);
    CHECK(w.median() == -60);
    CHECK(w.max() == -59);
    CHECK(w.count() == 5);
    w.add(-200);  // out of range readings are clipped, not dropped
    CHECK(w.count() == 6);
    CHECK_NEAR(mwToDbm(dbmToMw(-47)), -47, 1e-3);
}

static void testSts() {
    printf("servo packets\n");
    uint8_t b[sts::kMaxPacket];
    size_t n = sts::buildPing(b, 1);
    const uint8_t ping[] = {0xFF, 0xFF, 0x01, 0x02, 0x01, 0xFB};
    CHECK(n == sizeof(ping) && memcmp(b, ping, n) == 0);

    n = sts::buildRead(b, 1, sts::kRegPresentPosition, 2);
    const uint8_t rd[] = {0xFF, 0xFF, 0x01, 0x04, 0x02, 0x38, 0x02, 0xBE};
    CHECK(n == sizeof(rd) && memcmp(b, rd, n) == 0);

    n = sts::buildGoal(b, 2, 2048, 1000, 50);
    CHECK(n == 14);
    CHECK(b[2] == 2 && b[3] == 10 && b[4] == sts::kWrite && b[5] == sts::kRegAcc);
    CHECK(b[6] == 50 && b[7] == 0x00 && b[8] == 0x08);  // acc, position 2048 little-endian
    CHECK(b[11] == 0xE8 && b[12] == 0x03);              // speed 1000
    CHECK(b[13] == sts::checksum(b + 2, 11));

    CHECK(sts::encodeSigned(-5) == 0x8005);
    CHECK(sts::decodeSigned(0x8005) == -5);
    CHECK(sts::decodeSigned(0x0405, 10) == -5);  // load register: sign in bit 10
    CHECK(sts::decodeSigned(100) == 100);

    // A reply to "read 2 bytes": position 0x0834 = 2100, preceded by noise.
    uint8_t reply[] = {0x00, 0xFF, 0xFF, 0x01, 0x04, 0x00, 0x34, 0x08, 0x00};
    reply[8] = sts::checksum(reply + 3, 5);
    sts::Parser p;
    sts::Reply r;
    int got = 0;
    for (uint8_t c : reply) got += p.feed(c, r);
    CHECK(got == 1);
    CHECK(r.id == 1 && r.error == 0 && r.len == 2 && r.u16(0) == 2100);

    reply[6] ^= 0x01;  // corrupt one byte: must be rejected
    got = 0;
    for (uint8_t c : reply) got += p.feed(c, r);
    CHECK(got == 0);
}

static void testLink() {
    printf("link protocol\n");
    link::MsgSample s{};
    s.seq = 77;
    s.frames = 12;
    s.median = -63;
    s.max = -58;
    s.noise = -96;
    s.channel = 149;
    uint8_t b[link::kMaxFrame];
    size_t n = link::encode(b, link::kMsgSample, &s, sizeof(s));
    CHECK(n == sizeof(s) + 6);

    link::Parser p;
    link::Frame f;
    int got = 0;
    uint8_t junk[] = {0x11, 0xA5, 0xA5};  // noise and a false start before the frame
    for (uint8_t c : junk) got += p.feed(c, f);
    for (size_t i = 1; i < n; i++) got += p.feed(b[i], f);  // b[0] already supplied by junk
    CHECK(got == 1);
    link::MsgSample d{};
    CHECK(f.type == link::kMsgSample && f.as(d));
    CHECK(d.seq == 77 && d.median == -63 && d.channel == 149 && d.frames == 12);
    link::MsgHello wrong;
    CHECK(!f.as(wrong));  // size mismatch is refused

    b[6] ^= 0x40;  // corrupt: CRC must reject
    got = 0;
    for (size_t i = 0; i < n; i++) got += p.feed(b[i], f);
    CHECK(got == 0);

    CHECK(link::encode(b, 1, b, link::kMaxPayload + 1) == 0);
    CHECK(sizeof(link::MsgStation) <= link::kMaxPayload);
    CHECK(link::encode(b, link::kCmdPing, nullptr, 0) == 6);

    // Motor-controller messages survive the round trip unchanged.
    link::MsgPose pose{};
    pose.az = -123.5f;
    pose.el = 42.25f;
    pose.flags = link::kPoseTorque | link::kPoseCalibrated;
    n = link::encode(b, link::kMsgPose, &pose, sizeof(pose));
    got = 0;
    for (size_t i = 0; i < n; i++) got += p.feed(b[i], f);
    link::MsgPose back{};
    CHECK(got == 1 && f.type == link::kMsgPose && f.as(back));
    CHECK(back.az == -123.5f && back.el == 42.25f && back.flags == 3);
    CHECK(sizeof(link::MsgPose) == 9 && sizeof(link::CmdGoto) == 8);
}

static void testScan() {
    printf("scan\n");
    Scanner sc;
    ScanPlan plan;
    sc.begin(plan);
    AzEl p, prev{};
    int count = 0;
    bool inRange = true;
    float maxJump = 0;
    while (sc.next(p)) {
        if (p.az < plan.azMin - 0.01f || p.az > plan.azMax + 0.01f) inRange = false;
        if (p.el < plan.elMin - 0.01f || p.el > plan.elMax + 0.01f) inRange = false;
        if (count) maxJump = fmaxf(maxJump, separation(p, prev));
        prev = p;
        count++;
    }
    CHECK(inRange);
    CHECK(count == sc.total());
    // An even 5-degree grid on a hemisphere holds about 2*pi*sr / (5 deg)^2 = 825
    // points; a plain 71 x 19 raster would take 1349.
    printf("  %d points in a full-hemisphere scan\n", count);
    CHECK(count > 700 && count < 1000);
    CHECK(maxJump < 30);  // serpentine: no fly-back across the sky

    // Scan the simulated sky and find the source.
    for (AzEl src : {AzEl{40, 25}, AzEl{-120, 60}, AzEl{176, 5}, AzEl{10, 88}}) {
        Sky sky;
        sky.source = src;
        SkyMap map;
        sc.begin(plan);
        while (sc.next(p)) {
            float dbm;
            if (sky.measure(p, dbm)) map.put(p, dbm, sc.lastAzWidth());
        }
        AzEl found;
        float dbm;
        CHECK(map.peak(found, dbm));
        float err = separation(found, src);
        printf("  source az %.0f el %.0f: found az %.1f el %.1f, error %.1f deg\n", src.az, src.el,
               found.az, found.el, err);
        CHECK(err < 10);
    }

    // A 10-degree scan must leave no empty rows between the ones it visits.
    {
        SkyMap map;
        ScanPlan coarse;
        coarse.step = 10;
        sc.begin(coarse);
        while (sc.next(p)) map.put(p, -60, sc.lastAzWidth(), coarse.step);
        int holes = 0;
        for (int j = SkyMap::elIndex(0); j <= SkyMap::elIndex(90); j++)
            for (int i = SkyMap::azIndex(-170); i <= SkyMap::azIndex(170); i++)
                if (map.cell[j][i] == SkyMap::kEmpty) holes++;
        printf("  10-degree scan: %d points, %d empty cells inside the scanned area\n", sc.total(), holes);
        CHECK(holes == 0);
    }

    // Re-acquiring a lost source: a local scan around the last direction
    // is a fraction of the work of a full one and still finds a source that
    // has moved by most of a beamwidth. Narrow beam, as on a long-range antenna.
    {
        const float beam = 25;
        const AzEl last{60, 10};
        ScanPlan local = localPlan(last, beam, -175, 175, -15, 95);
        ScanPlan full;
        full.step = beam / 3;
        sc.begin(full);
        const int fullPoints = sc.total();
        sc.begin(local);
        const int localPoints = sc.total();
        Sky sky;
        sky.hpbw = beam;
        sky.source = {last.az + 15, last.el + 8};  // moved 17 degrees, two thirds of the beam
        SkyMap map;
        while (sc.next(p)) {
            float dbm;
            if (sky.measure(p, dbm)) map.put(p, dbm, sc.lastAzWidth(), local.step);
        }
        AzEl found;
        float dbm;
        CHECK(map.peak(found, dbm));
        float err = separation(found, sky.source);
        printf("  local re-acquire scan: %d points against %d for the whole sky, source found within %.1f deg\n",
               localPoints, fullPoints, err);
        CHECK(localPoints * 4 < fullPoints);
        CHECK(err < beam / 3);
        // At a travel limit the plan is clipped, not wrapped.
        ScanPlan edge = localPlan({170, 0}, beam, -175, 175, -15, 95);
        CHECK(edge.azMax <= 175 && edge.azMin < edge.azMax && edge.elMin >= -15);
    }

    SkyMap empty;
    AzEl f;
    float d;
    CHECK(!empty.peak(f, d));
}

static void testNmea() {
    printf("gps\n");
    Nmea gps;
    const char* gga = "$GPGGA,123519,5213.7890,N,02100.7340,E,1,08,0.9,110.4,M,34.0,M,,*";
    char line[128];
    uint8_t sum = 0;
    for (const char* c = gga + 1; *c != '*'; c++) sum ^= (uint8_t)*c;
    snprintf(line, sizeof(line), "%s%02X\r\n", gga, sum);
    int updates = 0;
    for (const char* c = line; *c; c++) updates += gps.feed(*c);
    CHECK(updates == 1);
    CHECK(gps.fix && gps.sats == 8);
    CHECK_NEAR(gps.lat, 52.229817, 1e-5);  // 52 deg 13.7890 min
    CHECK_NEAR(gps.lon, 21.012233, 1e-5);
    CHECK_NEAR(gps.alt, 110.4, 1e-3);

    snprintf(line, sizeof(line), "%s%02X\r\n", gga, (uint8_t)(sum ^ 1));  // wrong checksum
    updates = 0;
    for (const char* c = line; *c; c++) updates += gps.feed(*c);
    CHECK(updates == 0);

    // Southern / western hemisphere and "no fix".
    const char* nofix = "$GNGGA,000000,3351.0000,S,15112.0000,W,0,00,,,M,,M,,*";
    sum = 0;
    for (const char* c = nofix + 1; *c != '*'; c++) sum ^= (uint8_t)*c;
    snprintf(line, sizeof(line), "%s%02X\r\n", nofix, sum);
    updates = 0;
    for (const char* c = line; *c; c++) updates += gps.feed(*c);
    CHECK(updates == 1);
    CHECK(!gps.fix);
    CHECK_NEAR(gps.lat, -33.85, 1e-5);
    CHECK_NEAR(gps.lon, -151.2, 1e-5);
}

// Builds what the sensors would read for a known attitude, in a place where
// the magnetic field dips 67 degrees below the horizon (as in Poland).
struct SensorSim {
    Vec3 accel, mag;
    SensorSim(float heading, float pitch, float roll) {
        const float h = heading / kDegPerRad, p = pitch / kDegPerRad, r = roll / kDegPerRad;
        // Body axes in world (east, north, up), built step by step:
        // heading, then pitch about the left axis, then roll about the nose.
        const float f0[3] = {sinf(h), cosf(h), 0}, l0[3] = {-cosf(h), sinf(h), 0}, u0[3] = {0, 0, 1};
        float f[3], u1[3], l[3], u[3];
        for (int i = 0; i < 3; i++) {
            f[i] = f0[i] * cosf(p) + u0[i] * sinf(p);
            u1[i] = -f0[i] * sinf(p) + u0[i] * cosf(p);
        }
        for (int i = 0; i < 3; i++) {
            l[i] = l0[i] * cosf(r) + u1[i] * sinf(r);
            u[i] = -l0[i] * sinf(r) + u1[i] * cosf(r);
        }
        const float up[3] = {0, 0, 1};
        const float dip = 67 / kDegPerRad;
        const float b[3] = {0, 50 * cosf(dip), -50 * sinf(dip)};  // microtesla: north and down
        accel = {dot(f, up), dot(l, up), dot(u, up)};
        mag = {dot(f, b), dot(l, b), dot(u, b)};
    }
    static float dot(const float* a, const float* b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }
};

static void testAttitude() {
    printf("attitude\n");
    // Level, facing north: gravity straight up the z axis.
    float pitch, roll;
    tiltFromAccel({0, 0, 1}, pitch, roll);
    CHECK_NEAR(pitch, 0, 1e-3);
    CHECK_NEAR(roll, 0, 1e-3);

    // Recover a range of attitudes from simulated sensor readings.
    float worst = 0;
    for (float h : {0.0f, 45.0f, 137.0f, 270.0f, 359.0f})
        for (float p : {-30.0f, 0.0f, 20.0f})
            for (float r : {-25.0f, 0.0f, 40.0f}) {
                SensorSim s(h, p, r);
                tiltFromAccel(s.accel, pitch, roll);
                float hd = headingFromMag(s.mag, pitch, roll);
                worst = fmaxf(worst, fabsf(pitch - p));
                worst = fmaxf(worst, fabsf(roll - r));
                worst = fmaxf(worst, fabsf(wrap180(hd - h)));
            }
    printf("  45 attitudes recovered, worst error %.3f deg\n", worst);
    CHECK(worst < 0.05f);
    // Without tilt compensation a 20-degree pitch would move the heading by
    // tens of degrees at this magnetic dip; make sure the test would notice.
    {
        SensorSim s(137, 20, 0);
        float naive = wrap360(atan2f(s.mag.y, s.mag.x) * kDegPerRad);
        CHECK(fabsf(wrap180(naive - 137)) > 10);
    }
    CHECK_NEAR(headingFromMag(SensorSim(100, 0, 0).mag, 0, 0, 6.5f), 106.5, 0.01);  // declination

    // Direction conversion.
    Attitude level{90, 0, 0};  // facing east
    AzEl w = bodyToWorld({0, 0}, level);
    CHECK_NEAR(w.az, 90, 1e-2);
    CHECK_NEAR(w.el, 0, 1e-2);
    w = bodyToWorld({90, 30}, level);  // 90 degrees to the right of east is south
    CHECK_NEAR(w.az, 180, 1e-2);
    CHECK_NEAR(w.el, 30, 1e-2);
    w = bodyToWorld({0, 0}, {0, 25, 0});  // nose up 25: straight ahead looks 25 up
    CHECK_NEAR(w.el, 25, 1e-2);
    CHECK_NEAR(wrap180(w.az), 0, 1e-2);
    w = bodyToWorld({90, 0}, {0, 0, 30});  // right side down 30: looking right looks 30 down
    CHECK_NEAR(w.el, -30, 1e-2);
    CHECK_NEAR(w.az, 90, 1e-2);
    w = bodyToWorld({0, -45}, {200, 0, 0});  // antenna fixed 45 down, facing 200
    CHECK_NEAR(w.az, 200, 1e-2);
    CHECK_NEAR(w.el, -45, 1e-2);

    // Tilt filter: follows a steady nose-up rotation of 20 deg/s, and is not
    // thrown by a burst of sideways acceleration.
    {
        TiltFilter f;
        const float dt = 0.02f;
        float truth = 0;
        for (int i = 0; i < 100; i++) {
            truth = 20.0f * i * dt;
            f.update(SensorSim(0, truth, 0).accel, {0, -20, 0}, dt);
        }
        printf("  tilt filter after 2 s at 20 deg/s: %.1f (truth %.1f)\n", f.pitch(), truth);
        CHECK_NEAR(f.pitch(), truth, 1.0);
        TiltFilter g;
        for (int i = 0; i < 50; i++) g.update({0, 0, 1}, {0, 0, 0}, dt);
        for (int i = 0; i < 10; i++) g.update({0, 0.5f, 1}, {0, 0, 0}, dt);  // 0.2 s of 0.5 g sideways
        float alone, dummy;
        tiltFromAccel({0, 0.5f, 1}, dummy, alone);
        printf("  0.5 g sideways for 0.2 s: filter rolls %.1f deg, accelerometer alone says %.1f\n", g.roll(), alone);
        CHECK(fabsf(g.roll()) < alone / 2);
    }

    // A tilted vehicle turning on the spot, as in a turn scan: pitched 10
    // degrees, yawing 30 deg/s for 6 s. The gyroscope then sees rotation
    // about all three axes; the tilt estimate must not wander.
    {
        TiltFilter f;
        const float dt = 0.02f, rate = 30;
        float worstErr = 0;
        for (int i = 0; i < 300; i++) {
            SensorSim s(rate * i * dt, 10, 0);
            // Clockwise yaw is rotation about "down": minus the up direction,
            // which in body axes is what the accelerometer reads.
            Vec3 gyro{-rate * s.accel.x, -rate * s.accel.y, -rate * s.accel.z};
            f.update(s.accel, gyro, dt);
            worstErr = fmaxf(worstErr, fmaxf(fabsf(f.pitch() - 10), fabsf(f.roll())));
        }
        printf("  tilted 10 deg and turning 30 deg/s: worst tilt error %.2f deg\n", worstErr);
        CHECK(worstErr < 0.3f);
    }

    // A compass chip mounted turned 90 degrees clockwise, read while the
    // vehicle is pitched 20 degrees. Correcting the mount before the tilt is
    // taken out gives the right heading; adding 90 afterwards does not.
    {
        SensorSim s(137, 20, 0);
        // What the turned chip reports: its X is the body's right, its Y the body's forward.
        Vec3 chip{-s.mag.y, s.mag.x, s.mag.z};
        float pitch2, roll2;
        tiltFromAccel(s.accel, pitch2, roll2);
        float good = headingFromMag(mountToBody(chip, 90), pitch2, roll2);
        float bad = wrap360(headingFromMag(chip, pitch2, roll2) + 90);
        printf("  compass turned 90 deg, vehicle pitched 20: %.1f corrected first, %.1f corrected after (truth 137)\n", good, bad);
        CHECK_NEAR(wrap180(good - 137), 0, 0.05);
        CHECK(fabsf(wrap180(bad - 137)) > 5);
        Vec3 mirrored{s.mag.x, -s.mag.y, s.mag.z};  // a chip whose Y arrow points right
        CHECK_NEAR(wrap180(headingFromMag(mountToBody(mirrored, 0, true), pitch2, roll2) - 137), 0, 0.05);
    }

    // Compass calibration: readings shifted and stretched by nearby iron.
    {
        MagCalibration cal;
        cal.begin();
        auto distort = [](Vec3 m) { return Vec3{m.x * 1.3f + 40, m.y * 0.8f - 25, m.z}; };
        for (int h = 0; h < 360; h += 5) cal.add(distort(SensorSim((float)h, 0, 0).mag));
        CHECK(cal.finish(10));
        float before = 0, after = 0;
        for (int h = 0; h < 360; h += 15) {
            Vec3 raw = distort(SensorSim((float)h, 0, 0).mag);
            before = fmaxf(before, fabsf(wrap180(headingFromMag(raw, 0, 0) - h)));
            after = fmaxf(after, fabsf(wrap180(headingFromMag(cal.apply(raw), 0, 0) - h)));
        }
        printf("  compass: worst heading error %.0f deg uncalibrated, %.2f deg calibrated\n", before, after);
        CHECK(before > 30);
        CHECK(after < 0.5f);
        MagCalibration poor;
        poor.begin();
        for (int h = 0; h < 20; h += 5) poor.add(SensorSim((float)h, 0, 0).mag);
        CHECK(!poor.finish(10));  // a 20-degree wiggle is not a calibration
    }
}

static void testLocate() {
    printf("locate\n");
    // Warsaw-ish reference; one degree of latitude is about 111 km.
    LocalPoint p = toLocal(52.2310, 21.0100, 52.2300, 21.0100);
    CHECK_NEAR(p.north, 111.2, 0.5);
    CHECK_NEAR(p.east, 0, 0.01);
    p = toLocal(52.2300, 21.0110, 52.2300, 21.0100);
    CHECK_NEAR(p.east, 68.1, 0.5);  // a longitude step shrinks by cos(latitude)
    double lat, lon;
    fromLocal({120, -340}, 52.23, 21.01, lat, lon);
    LocalPoint back = toLocal(lat, lon, 52.23, 21.01);
    CHECK_NEAR(back.east, 120, 0.01);
    CHECK_NEAR(back.north, -340, 0.01);

    // A transmitter 300 m east and 200 m north, seen from five places with
    // 5 degrees of bearing noise.
    const LocalPoint tx{300, 200};
    const LocalPoint from[] = {{0, 0}, {150, -100}, {400, -50}, {-50, 250}, {250, 450}};
    std::mt19937 rng(7);
    std::normal_distribution<float> noise(0, 5);
    BearingFix fix;
    for (LocalPoint f : from) {
        float bearing = atan2f(tx.east - f.east, tx.north - f.north) * kDegPerRad;
        fix.add(f, bearing + noise(rng));
    }
    LocalPoint est;
    float rms;
    int behind;
    CHECK(fix.solve(est, rms, behind));
    float miss = hypotf(est.east - tx.east, est.north - tx.north);
    printf("  5 bearings with 5 deg noise: %.0f m from the truth, lines miss by %.0f m RMS\n", miss, rms);
    CHECK(miss < 40);
    CHECK(behind == 0);

    // Exact bearings give the exact point.
    fix.clear();
    for (LocalPoint f : from) fix.add(f, atan2f(tx.east - f.east, tx.north - f.north) * kDegPerRad);
    CHECK(fix.solve(est, rms, behind));
    CHECK_NEAR(est.east, 300, 0.05);
    CHECK_NEAR(est.north, 200, 0.05);
    CHECK(rms < 0.05f);

    // Bearings taken along one line cannot fix a position.
    fix.clear();
    fix.add({0, 0}, 45);
    fix.add({100, 100}, 45.5f);
    CHECK(!fix.solve(est, rms, behind));
    fix.clear();
    fix.add({0, 0}, 10);
    CHECK(!fix.solve(est, rms, behind));  // one bearing is a line, not a point

    // A bearing that points away from the crossing is counted.
    fix.clear();
    fix.add({0, 0}, 45);
    fix.add({200, 0}, 315);
    fix.add({100, 300}, 0);  // looks north, but the crossing is to its south
    CHECK(fix.solve(est, rms, behind));
    CHECK(behind == 1);
}

// Runs the tracker and returns the RMS pointing error over `cycles` cycles,
// after first letting it settle for `settle` cycles.
static float runTracker(Tracker& t, Sky& sky, int settle, int cycles, float driftAzPerCycle = 0) {
    double sum = 0;
    int n = 0;
    for (int c = 0; c < settle + cycles && !t.lost(); c++) {
        for (int i = 0; i < 5; i++) {
            float dbm = 0;
            bool ok = sky.measure(t.nextPoint(), dbm);
            t.report(ok, dbm);
        }
        sky.source.az = wrap180(sky.source.az + driftAzPerCycle);
        if (c >= settle) {
            float e = separation(t.centre(), sky.source);
            sum += e * e;
            n++;
        }
    }
    return n ? (float)sqrt(sum / n) : 0;
}

// Expected accuracy. With beamwidth B, dither B/2 and reading noise s (dB),
// one cycle locates the peak to sqrt(2)*s*B/24 degrees per axis, and a loop
// gain g averages that down by sqrt(g/(2-g)). For B = 40, s = 2, g = 0.5:
// 4.7 * 0.58 = 2.7 degrees per axis, 3.8 degrees RMS on the sky, which costs
// 12*(3.8/40)^2 = 0.1 dB of signal. The bounds below leave about 50 % margin.
static void testTracker() {
    printf("tracker\n");
    {
        Sky sky;
        Tracker t;
        t.start({55, 12});  // about 19 degrees off the source
        float err = runTracker(t, sky, 8, 60);
        printf("  static source, start 19 deg off: %.1f deg RMS\n", err);
        CHECK(err < 6);
        CHECK(!t.lost());
        CHECK(t.peakDbm() > -62);
    }
    {
        Sky sky;
        sky.noiseDb = 4;  // heavy multipath: expect twice the error
        Tracker t;
        t.start({30, 30});
        float err = runTracker(t, sky, 8, 200);
        printf("  static source, 4 dB noise: %.1f deg RMS\n", err);
        CHECK(err < 12);
        CHECK(!t.lost());
    }
    {
        Sky sky;
        Tracker t;
        t.start(sky.source);
        float err = runTracker(t, sky, 0, 60, 1.5f);  // source walks 90 degrees
        printf("  source moving 1.5 deg/cycle: %.1f deg RMS\n", err);
        CHECK(err < 8);
        CHECK(!t.lost());
    }
    {
        Sky sky;
        sky.source = {-175, 40};  // tracking across the +/-180 seam
        Tracker t;
        t.start({170, 35});
        float err = runTracker(t, sky, 8, 60);
        printf("  source across the azimuth seam: %.1f deg RMS\n", err);
        CHECK(err < 6);
    }
    {
        // A head with end stops at +/-175: a source near the stop must be held
        // without ever sending the head round to the other end.
        Sky sky;
        sky.source = {168, 20};
        Tracker t;
        t.cfg.azMin = -175;
        t.cfg.azMax = 175;
        t.start({150, 25});
        float maxSwing = 0;
        AzEl prev = t.nextPoint();
        double sum = 0;
        int n = 0;
        for (int c = 0; c < 68; c++) {
            for (int i = 0; i < 5; i++) {
                AzEl p = t.nextPoint();
                maxSwing = fmaxf(maxSwing, fabsf(p.az - prev.az));
                prev = p;
                float dbm = 0;
                bool ok = sky.measure(p, dbm);
                t.report(ok, dbm);
            }
            if (c >= 8) { float e = separation(t.centre(), sky.source); sum += e * e; n++; }
        }
        float err = (float)sqrt(sum / n);
        printf("  source 7 deg from an end stop: %.1f deg RMS, largest azimuth move %.0f deg\n", err, maxSwing);
        CHECK(err < 8);
        CHECK(maxSwing < 60);
        CHECK(t.centre().az <= 175 && t.centre().az >= -175);
    }
    {
        // Carried in the hand: the base turns under the head. With the turn
        // fed in from the compass the tracker holds a still source; without
        // it, it has to find the source again.
        auto carried = [](bool compensate) {
            Sky sky;
            Tracker t;
            t.start(sky.source);
            double sum = 0;
            int n = 0;
            for (int c = 0; c < 80; c++) {
                for (int i = 0; i < 5; i++) {
                    float dbm = 0;
                    bool ok = sky.measure(t.nextPoint(), dbm);
                    t.report(ok, dbm);
                    // The hand turns the base 1 degree per reading, back and forth:
                    // in head angles the source moves the other way.
                    float turn = (c / 8) % 2 ? -1.0f : 1.0f;
                    sky.source.az = wrap180(sky.source.az - turn);
                    if (compensate) t.shiftAz(-turn);
                }
                float e = separation(t.centre(), sky.source);
                sum += e * e;
                n++;
            }
            return (float)sqrt(sum / n);
        };
        float with = carried(true), without = carried(false);
        printf("  base turning 5 deg/cycle in the hand: %.1f deg RMS with the compass feeding the tracker, %.1f without\n", with, without);
        CHECK(with < 6);
        CHECK(without > with + 2);
    }
    {
        Sky sky;
        sky.source = {20, 80};  // near the zenith, where azimuth is ill-conditioned
        Tracker t;
        t.start({60, 70});
        float err = runTracker(t, sky, 8, 60);
        printf("  source at 80 deg elevation: %.1f deg RMS\n", err);
        CHECK(err < 8);
    }
    {
        Sky sky;
        Tracker t;
        t.start(sky.source);
        runTracker(t, sky, 0, 5);
        CHECK(!t.lost());
        sky.present = false;
        runTracker(t, sky, 0, 2);
        CHECK(!t.lost());  // two silent cycles are tolerated
        runTracker(t, sky, 0, 1);
        CHECK(t.lost());   // the third declares the source lost
    }
}

int main() {
    testGeometry();
    testStats();
    testSts();
    testLink();
    testScan();
    testTracker();
    testNmea();
    testAttitude();
    testLocate();
    printf("%d checks, %d failed\n", g_checks, g_failed);
    return g_failed ? 1 : 0;
}
