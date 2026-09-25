# KESTREL Scout — project overview

**A small open-source quadruped project focused on understandable reactive autonomy and careful testing.**

## The problem I want to explore

Small maker robots are usually remote-controlled or run fixed animations. I want to explore how far a low-cost printable quadruped can go with transparent sensor-driven choices, safe stop states, and test notes that other students can reproduce.

## Proposed build

KESTREL builds on the scale and maker accessibility of the Sesame quadruped. Planned additions include an ESP32-S3-class controller, independently powered servo outputs, a front range sensor, an IMU, downward-facing floor sensors, a bumper input, and a modular printed sensor mount. Its first autonomy scope is intentionally narrow: slow short bursts, frequent re-checks, obstacle-aware turns, and a stop on possible floor edge or invalid critical sensing.

## What is already complete

The repository has an initial C++ behavior-policy core, host-side regression tests, continuous-integration setup, a funding/budget plan, and CAD intake instructions. The concept art is illustrative, not prototype photography.

## What the grant makes possible

A complete build budget is capped at **$400 USD**, including a used/refurbished printer and basic starter tools. The current estimate is $331 for parts and tools plus a $69 shipping/tax/price reserve. It assumes a 3D printer costing no more than $130 and U.S.-price availability; all prices must be verified before purchase.

## What success looks like

A documented, assembled robot that can be rebuilt from the repository; measured stable power and sensor behavior; repeatable supervised tests on a bounded flat surface; a firmware suite with passing host tests; and a demo that openly reports limitations and failures.

## Status and request

**Early software prototype; physical build not yet assembled or tested.** Funding has not been received and equipment has not been purchased. I am seeking up to $400 for the listed parts, printer, and tools. [Maker's motivation, experience, timeline, and collaborators should be added by the applicant in their own words before submission.]

**Repository:** [KESTREL Scout on GitHub](../README.md)  
**Detailed plan:** [Project plan and bill of materials](PROJECT_PLAN.md)  
**Safety and test evidence:** [Safety notes](SAFETY.md) · [Test plan](TEST_PLAN.md)
