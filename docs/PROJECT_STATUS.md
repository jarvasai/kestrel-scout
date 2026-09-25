# Project status

**Snapshot:** 2026-09-26  
**Overall:** Early software prototype / physical build not started  
**Hardware assembled:** No  
**CAD reviewed:** No; maker will supply models  
**Funded or purchased:** No; the listed grant budget is a proposal

## Evidence-backed status

| Area | Status | Evidence or next step |
| --- | --- | --- |
| Product definition | Concept drafted | `docs/PROJECT_PLAN.md` |
| Behavior/safety policy core | Implemented; host tested | `firmware/kestrel-core/` and host CI |
| Servo adapter | Not implemented | Needs actual joint geometry, servo calibration, and board pinout |
| Range/IMU/floor sensor drivers | Not implemented | Select actual modules and verify libraries/pin assignments |
| CAD and printed adaptations | Pending maker files | Handoff area: `hardware/cad/source/` |
| Power system | Not measured | Must bench-test current, voltage sag, heating, and cutoff behavior |
| Physical scout behavior | Not tested | Test log: `docs/TEST_PLAN.md` |
| UI/API changes | Not implemented | Keep disabled until sensor and stop path are validated |

## What changes this status

- **CAD received** → log filename, unit system, author, revision, and license; inspect fit before marking reviewed.
- **First assembly complete** → add dated photographs and build notes; do not claim autonomy from assembly alone.
- **Firmware integrated** → add board/sensor versions, pin map, reproducible build instructions, and CI evidence.
- **Bench tests pass** → record method, surface, sensor calibration, supply voltage/current, failures, and retest count.
- **Field demonstration** → only describe the tested conditions; maintain a visible limitations section.

Do not remove or soften the “not built/not tested” status until the corresponding evidence is in the repository.
