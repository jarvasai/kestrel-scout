# KESTREL behavior core (hardware-independent prototype)

This folder contains a small, deterministic C++ behavior supervisor for the KESTREL concept. It is intentionally separate from Sesame's Arduino `.ino` firmware: its job is to make policy decisions, **not** drive servos or claim that sensors are wired and calibrated.

## Current behavior

- With a mission enabled and fresh critical sensors, request one 250 ms forward burst when the front range is at least 350 mm.
- If an obstacle is closer, use fresh left/right sweep measurements; request a 250 ms turn toward a side at least 450 mm clear. If neither side meets that threshold, remain stopped and retry after a pause.
- Stop between bursts so the caller can refresh sensor data before deciding again; a newly sensed obstacle interrupts a forward burst.
- Latch a stop on emergency stop, bumper input, possible floor edge, excessive tilt, or stale/invalid critical sensors during an active mission.
- Clear a latched fault only when the mission is disarmed and sensors report a safe state.

## Board adapter contract

The future Arduino adapter must provide valid sensor samples with timestamps and map `Action` values to **calibrated, bounded, interruptible** Sesame gaits. It must also enforce a hardware-level/manual stop path. The core does not generate joint angles, control a pan servo, monitor battery voltage, or make the floor sensors intrinsically reliable. Until those pieces are implemented and physically tested, do not connect this policy output to an assembled walking robot.

`leftFloorPresent` and `rightFloorPresent` mean “the calibrated sensor detects the intended safe floor surface.” If that meaning cannot be validated for the test floor, keep autonomous mode disabled. Stale floor/IMU/front-range data fail closed while a mission is active.

## Run host tests

From the repository root:

```sh
g++ -std=c++11 -Wall -Wextra -Werror \
  firmware/kestrel-core/KestrelCore.cpp \\
  firmware/kestrel-core/tests/test_kestrel_core.cpp \\
  -o /tmp/kestrel-core-tests
/tmp/kestrel-core-tests
```

These tests exercise state-machine policy only. They are not a substitute for bench, sensor, power, or physical safety testing.
