# Roadmap

No stage is marked complete without the evidence listed. Timings are estimates after CAD and funding are available; they are not delivery promises.

| Stage | Work | Completion evidence |
| --- | --- | --- |
| 0 — Software baseline | Keep the portable behavior policy small, buildable, and reviewed | Host CI passes; state transitions and thresholds documented |
| 1 — CAD intake | Review maker-supplied CAD for units, licenses, dimensions, clearances, and sensor mounting | `hardware/cad/source/README.md` register updated; fit notes/photos included |
| 2 — Mechanical fit | Print one body set and sensor-mount prototypes; correct collisions and cable pinch points | CAD revision and slicer settings recorded; assembled body photos; servos move freely unloaded |
| 3 — Power and base gait | Wire fused power; calibrate all servos; measure voltage/current during staged movement | Wiring diagram, component datasheets, measured voltage/current/temp log; reliable manual stop |
| 4 — Sensors | Add one module at a time (IMU, range sensor, floor sensors, bumpers); validate readings on the actual test floor | Versioned pin map, library versions, calibration procedure, sensor fault tests |
| 5 — Supervised autonomy | Add a board adapter behind a disabled-by-default flag; enable only short interruptible actions | Software tests, physical stop trials, raw logs, failure notes, repeated successful floor tests |
| 6 — Public demo/release | Reproduce build from documentation and publish a real demonstration | Dated build photos/video, release checklist, updated project-status table, final spend reconciliation |

## Release gates

1. Do not connect behavior outputs to the live servo movement path before manual stop and bounded servo calibration are established.
2. Do not enable edge response until each floor sensor is calibrated on the actual surface and a supervised stop-distance test has been repeated.
3. Do not claim autonomous navigation; version 1 is obstacle-aware, short-burst reactive behavior, not mapping or route planning.
4. Do not mark hardware complete until its bill of materials, wiring, code revision, and measurements are in the repository.
