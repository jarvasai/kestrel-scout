# Test plan and evidence log

**Status:** procedures proposed; no physical test results recorded.  
**Rule:** do not backfill a pass from memory. Capture the setup, code revision, raw result, and any failure.

## Test record template

```text
Date / operator:
Robot and firmware commit:
Board / sensor / battery revisions:
Floor and lighting:
Test setup and safety boundary:
Sensor calibration / threshold:
Supply voltage before / during movement:
Temperature and current measurement method:
Trials and outcome (including failures):
Photos / serial logs / data files:
Pass, fail, or not run:
Limitations / next action:
```

## Software tests (implemented on host)

| Check | Expected behavior | Status |
| --- | --- | --- |
| Clear front path | One bounded forward-action request; stop between bursts | Implemented in host tests |
| Obstacle during a forward burst | Stop immediately; re-evaluate before selecting a turn | Implemented in host tests |
| Both sides blocked | Stay stopped / blocked | Implemented in host tests |
| Side scan chooses a direction | Keep selected direction for the complete short burst | Implemented in host tests |
| Emergency stop / bumper / possible floor edge | Latch fault and request stop | Implemented in host tests |
| Excessive or non-finite tilt | Latch fault and request stop | Implemented in host tests |
| Stale front, IMU, or floor sample | Fail closed during an active mission | Implemented in host tests |
| Safe reset | Reset only while disarmed, critical sensors fresh, and readings safe | Implemented in host tests |

## Physical tests (all pending)

1. **Power-off mechanical inspection:** verify joint clearance, no trapped wiring, secure horns and fasteners, free movement by hand.
2. **Unloaded servo calibration:** test each motor independently with leg/joint loads removed; record center/min/max pulse and direction before attaching horns.
3. **Power bench test:** verify polarity, fuse, battery/charger compatibility, separate logic/servo rails, common signal ground, regulator ratings, peak voltage sag, current, and temperature. Stop immediately on resets or heating.
4. **Sensor calibration:** compare front ToF distances to a ruler across matte/dark/bright surfaces; record misses and range. Verify IMU stationary/baseline and tilt direction. Calibrate floor sensors over the exact test mat and inspect sunlight/lighting effects.
5. **Fault injection:** disconnect/disable one sensor at a time; confirm the mission stays stopped and exposes a fault. Verify emergency stop and reset path with legs raised and a spotter.
6. **Bounded-motion trial:** robot tethered or otherwise constrained, on a taped flat floor with a clear boundary, low servo speed, person ready to isolate battery. Test one 250 ms action at a time.
7. **Obstacle/edge trial:** begin with soft objects and a wide safety margin. Repeat tests with logged distances and failures; never use real stairs as an initial test target.
8. **Regression:** repeat safety tests after any sensor, threshold, gait, wiring, enclosure, or power change.

### Results

| Date | Commit | Test | Result | Evidence |
| --- | --- | --- | --- | --- |
| — | — | No physical tests yet | Not run | Waiting for CAD and hardware |
