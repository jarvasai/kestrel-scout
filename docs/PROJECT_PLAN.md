# KESTREL Scout — project plan

**Version:** 0.1 concept and build plan  
**Budget ceiling:** USD $400 all-in, including printer and starter tools  
**Status:** Design proposal; no physical prototype or hardware validation yet

## 1. The idea

Turn the Sesame quadruped into **KESTREL**, a small indoor scouting robot that senses its surroundings and can respond safely to simple missions. It keeps Sesame's printable eight-servo body, expressive OLED face, and open firmware foundation, but changes the project from “a robot that plays movement animations” into “a sensor-equipped robot that makes simple local decisions and reports what it senses.”

The differentiator is the **complete behavior loop**, not a claim of magical AI:

1. The operator gives a simple command from the existing phone/web/companion-app path.
2. KESTREL checks its own state and sensor readings.
3. It scans for a nearby obstacle, pauses or chooses a basic turn, and can stop when its floor-edge sensors indicate a possible drop.
4. It reports mode, distance, tilt/fall state, and battery status where the hardware supports it; the face gives clear status feedback.

This is an **indoor demonstration robot for slow movement on a flat, bounded floor**, not a production inspection robot or a stair-safe device.

## 2. What makes it visibly different from stock Sesame

| Stock project foundation | KESTREL direction |
| --- | --- |
| Eight servos play programmed gaits/emotes | A lightweight behavior state machine selects between idle, scan, approach/stop, turn, recover, and emergency-stop states |
| OLED is mainly an expressive face | Face becomes a status display too: mission, obstacle, edge warning, fall/tilt, and low-battery indication |
| Wi-Fi/API provides remote control | Keep the existing API/control path; add structured sensor/mission status rather than replace the whole stack |
| No standard obstacle/edge sensing in the base build | Add a front time-of-flight range sensor, a small scanning mount, an IMU, downward-facing floor sensors, and bump switches |
| Body is a fixed build | Add a removable, printed sensor mast/pod and a small, lightweight accessory bay; payload strength remains to be tested |
| Voice is an optional companion-app feature | Reuse the existing companion app for high-level commands; keep immediate stop/edge reactions local to the robot |

**Not in version 1:** expensive LiDAR, autonomous mapping, cloud AI, heavy payloads, high-speed walking, or vision-based person following. Those would exceed the budget, add failure points, and overstate what the micro-servos and sensors can safely do.

## 3. Hardware concept

- **Body:** Sesame's existing printable frame, covers, and eight 180° MG90S servos. Keep the stock geometry initially; print only a sensor mast, sensor guards, and accessory-bay adapters after the basic robot works.
- **Controller:** ESP32-S3 development board with Wi-Fi/Bluetooth LE. A board with PSRAM is preferred if future camera work is desired, but version 1 does not depend on a camera.
- **Servo output:** PCA9685 16-channel PWM board for servo pulses, leaving MCU resources available for Wi-Fi and sensors. Servo power still comes from a separate high-current 5V rail, not the controller's logic pin.
- **Sensing:**
  - One front VL53L0X time-of-flight sensor on a printed pan bracket; a spare servo sweeps left/center/right for a crude obstacle scan.
  - IMU for tilt/fall detection and telemetry; it is **not** a promise of dynamic balance.
  - Two downward-facing IR reflectance sensors for a calibrated “possible edge” warning. Floor color, sunlight, and sensor placement can affect readings.
  - One or two low-cost bumper switches as a last-resort contact input.
- **Display:** Retain the 128×64 OLED from the Sesame BOM.
- **Power:** Use the Sesame-compatible 2S battery/charger path only with the matching charger, a suitable regulator, fuse, strain relief, and correct polarity. Keep the servo supply separate from logic power and join grounds at the planned power distribution point. The official Sesame BOM calls for at least 5V/3A; do not assume that figure proves a particular battery/regulator can safely tolerate every servo stall condition. Validate rail voltage under load before fitting the body.

## 4. Firmware plan

Keep the current Sesame firmware as the baseline and add modules rather than replacing the working portal and animation system all at once:

1. **Sensor layer:** non-blocking reads and validity/timeouts for ToF, IMU, floor sensors, and bumpers.
2. **Safety supervisor:** highest-priority stop state; sensor faults should disable autonomous movement, not be interpreted as a clear path.
3. **Behavior state machine:** `IDLE → SCAN → MOVE_SHORT → VERIFY → TURN/STOP`, with `EDGE_ALERT`, `FALL_RECOVERY`, and `FAULT` paths. Start with short, timed movement bursts; verify movement in a tethered, open test area before longer commands.
4. **Servo abstraction:** calibrated neutral offsets and movement bounds per joint, with slew limits to reduce abrupt motion/current spikes. Do not assume the PCA9685 alone solves power brownouts.
5. **API additions:** read-only `/api/status` sensor/mode fields first; add explicit mission commands only after the stop behavior is reliable. Preserve manual control and add a dead-man/stop control.
6. **Face/status layer:** retain expressions, but add readable warning states (edge, obstacle, tilted, low battery, sensor fault).
7. **Companion-app integration:** reuse the existing app/API for mission selection and status. Cloud inference or paid AI services are deliberately not required.

### Version-1 acceptance tests

- All servos can be calibrated individually with joints safely unloaded.
- Sensor readings are stable enough to detect a nearby test object at walking speed; verify distance with a ruler.
- Edge sensors are calibrated on the actual test floor and stop the robot in repeated tests before the edge; if results vary, autonomous edge mode stays disabled.
- A sensor disconnect or invalid reading leads to stop/fault, never “path clear.”
- Manual stop interrupts every autonomous state promptly.
- The robot completes short, slow obstacle-response tests on a flat, clear floor without resets or controller brownouts.
- Battery and regulator temperatures/voltages remain within their rated limits during repeated motion tests.

These are prototype acceptance targets, not guarantees of reliable navigation or safety around people, pets, stairs, or fragile objects.

## 5. All-in budget target (USD)

This is a **planning estimate using U.S. reference pricing**. To leave room for tax, shipping, and price changes, the printer must be **used/refurbished and cost no more than $130 before checkout**. The $69 reserve is part of the cap, not extra spending permission.

| Item | Target cap | Notes |
| --- | ---: | --- |
| Used/refurbished FDM printer, at least 220×220mm bed | $130 | Hard ceiling; inspect condition, hotend, bed, and power supply before buying. |
| PLA filament, 1 kg | $18 | Includes stock replacement parts and the sensor adapters. |
| Basic starter tools | $25 | Budget soldering iron/solder, basic multimeter, small cutters and screwdriver set. Borrow tools if this package is too poor-quality. |
| 8 × MG90S 180° servos | $40 | Target assumes about $5 each; check range and seller quality. |
| ESP32-S3 controller | $13 | Choose an in-stock equivalent; listed reference was temporarily marked “restocking soon.” |
| PCA9685 servo PWM board | $8 | Budget estimate. |
| Front VL53L0X ToF sensor | $15 | Current Adafruit listing is $14.95. |
| IMU module | $6 | Budget estimate; verify chip/library compatibility before purchase. |
| Pair of downward-facing IR floor sensors | $8 | Budget estimate; must be calibrated on the test floor. |
| Bumper switches | $3 | Budget estimate. |
| OLED display | $8 | Stock Sesame-compatible SSD1306 display estimate. |
| 5V high-current regulator/UBEC | $15 | Budget estimate; verify rating, cooling, and transient capacity against the selected battery and servos. |
| Battery plus its correct charger | $20 | Budget allowance only; use a matched, correctly rated pack/charger, never loose unprotected cells. |
| Wire, fuse, switch, capacitor, connectors | $14 | Budget estimate. |
| Fasteners and heat-shrink | $8 | Budget estimate. |
| **Estimated parts/tools subtotal** | **$331** |  |
| **Checkout reserve for shipping/tax/variance** | **$69** | Do not spend the reserve on optional upgrades until checkout totals are known. |
| **Hard all-in cap** | **$400** |  |

### Budget reality check

The live Creality U.S. product page lists a new Ender-3 V3 SE at **$199**. Replacing the $130 used-printer target with that price raises the parts/tools subtotal to **$400 before tax or shipping**, so a new printer at that price does **not** fit the all-in cap. If a suitable used/refurbished printer cannot be found for $130 or less, the honest fallback is to use a library/makerspace printer or pause and revise the budget—not silently exceed $400.

The table's smaller parts/tool amounts are caps, not guaranteed checkout quotes. This budget currently assumes U.S. availability and does not include a computer or phone because the Sesame software uses devices the builder already owns. If buying outside the U.S., local component prices, import duty, and shipping may change the plan materially.

## 6. Build sequence

1. **Buy only after the printer and essential-power quotes fit the cap.** Keep the order subtotal and checkout reserve visible.
2. **Print and assemble stock Sesame first.** Calibrate all eight servos without the leg joints attached, following the upstream build guide.
3. **Bench-test the power system.** Measure 5V under movement load; fuse the battery input; confirm the regulator and wiring ratings.
4. **Add one sensor at a time:** IMU and OLED status first, then the front ToF scan, then the downward sensors and bumpers.
5. **Implement the safety supervisor before autonomous gait selection.** Manual stop and sensor-fault handling come first.
6. **Test on a taped-off, flat floor** with the robot tethered/within reach and low speed. Do not test near stairs, pets, or people.
7. **Only after repeatable bench results:** publish a new project name, enclosure styling, build guide, firmware setup guide, and demo video. Do not alter or publish to the upstream author's repository without a separate explicit instruction.

## 7. Repository notes and references

The plan is based on the public [Sesame Robot repository](https://github.com/dorianborian/sesame-robot), especially its [hardware BOM](https://github.com/dorianborian/sesame-robot/blob/main/hardware/bom/README.md), [printing guide](https://github.com/dorianborian/sesame-robot/blob/main/hardware/printing/README.md), [build guide](https://github.com/dorianborian/sesame-robot/blob/main/docs/build-guide/README.md), and [firmware documentation](https://github.com/dorianborian/sesame-robot/blob/main/firmware/README.md).

Price/spec references checked while drafting:

- [Creality Ender-3 V3 SE official store page](https://store.creality.com/products/ender-3-v3-se-3d-printer): listed at $199 at time checked.
- [PiShop Waveshare MG90S servo](https://www.pishop.us/product/mg90s-micro-servo-metal-gear/): listed at $4.95 each, with 180° range stated.
- [RobotShop Waveshare ESP32-S3 board](https://www.robotshop.com/products/waveshare-esp32-s3-microcontroller-24ghz-wi-fi-development-board-240mhz-dual-core-processor-w-headers): $12.53 listed, but page said restocking soon at time checked.
- [Adafruit VL53L0X sensor](https://www.adafruit.com/product/3317): listed at $14.95.
- [Bambu Lab battery and power supplies](https://us.store.bambulab.com/collections/power-supplies): Sesame's named battery listed from $4.59 and its matching charger at $5.49; verify pack suitability and delivery before ordering.
