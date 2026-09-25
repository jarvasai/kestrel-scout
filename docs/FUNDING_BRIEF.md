# Funding brief (draft for the maker to personalize)

> **Do not submit this draft unchanged if it does not describe your own motivation, experience, schedule, and plan.** Replace every bracketed field with true details. No award has been received and no hardware purchases are represented as completed.

## Short project description

**KESTREL Scout** is my proposed open-source, low-cost quadruped robotics build. I want to turn a small printable robot into a more understandable indoor scout: instead of only replaying animations, it will read nearby distance and tilt sensors, take short controlled steps, pause to re-check, and stop when its sensors detect a possible hazard or fail. I am building the software and safety policy first, then will adapt the CAD, electronics, and movement to the physical model. I plan to publish the design files, firmware, wiring notes, test results, and failures so another student can reproduce and improve the project.

**My reason for building this:** [In your own words: what sparked your interest, what you have tried, and what you want to learn.]  
**My relevant experience:** [State the real tools, programming, classes, clubs, or projects you have used; “beginner” is an honest answer.]  
**Schedule / collaborators:** [Add your real timeline, school/lab access, and who will help supervise or review battery and soldering work.]

## What is already done—and what is not

Completed in this repository: an initial C++ behavior-policy core, host tests, and a proposed bill of materials and build plan. Not completed: CAD review, printer/hardware purchase, robot assembly, ESP32 sensor-driver integration, walking-gait integration, and any physical safety or navigation tests. The concept illustration is AI-generated concept art and is labeled as such; it is not a photograph of the robot.

## Funding request: maximum $400 (USD estimate)

| Use | Estimate | Why it is needed |
| --- | ---: | --- |
| Used/refurbished FDM printer, ≥220×220 mm bed | $130 | Print the quadruped and iterate on custom sensor mounts; hard purchase ceiling |
| PLA filament (1 kg) | $18 | Body parts and iteration/test brackets |
| Starter tools | $25 | Basic soldering, multimeter, cutters, and screwdrivers; borrow quality tools if possible |
| Eight 180° metal-gear micro servos | $40 | Leg actuation baseline; price/quality must be checked before purchase |
| ESP32-S3-class controller | $13 | Wi-Fi/Bluetooth-capable low-cost controller |
| Servo PWM breakout | $8 | Separate servo-signal control from logic work |
| Range, IMU, floor sensors, bumpers, OLED | $40 | Reactive obstacle, tilt, possible edge, and status sensing |
| Regulator, battery and matched charger | $35 | Independent servo rail and portable power, only after compatibility checks |
| Wiring, fuse, switch, capacitor, fasteners, heat-shrink | $22 | Safe assembly and serviceable prototypes |
| **Estimated parts and tools** | **$331** |  |
| **Shipping, tax and price contingency** | **$69** | Held in reserve; not pre-assigned to optional upgrades |
| **Total requested / cap** | **$400** | U.S. estimate; final receipts will be reconciled |

A new Ender-3 V3 SE was listed at $199 when checked; using that new-printer price makes the parts-and-tools subtotal about $400 before tax and shipping, leaving no checkout reserve. This plan therefore depends on finding a suitable used/refurbished 3D printer for no more than $130, or arranging access to one without charging it to the grant. If neither happens, I will revise the scope before purchasing rather than exceed the cap.

## Measurable outcomes

- A documented and reproducible physical build, with versioned CAD and a full parts list.
- Firmware that builds from documented steps and has automated behavior-policy tests.
- Sensor calibration notes and measured power data, including failure conditions.
- Supervised, repeatable short-burst motion and fault-stop tests on a bounded flat test area.
- A short demonstration video and a public repository that distinguishes tested results from future goals.

## Responsible use of funds

I will compare suppliers before purchasing, keep itemized receipts, log substituted parts and actual prices, retain the $69 contingency until checkout totals are known, and report unused funds according to the program's rules. I will not claim testing, purchases, or project features that have not happened.
