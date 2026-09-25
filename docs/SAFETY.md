# Safety notes

KESTREL is a student/maker prototype, not a certified robot. It has not yet been assembled or safety-tested. These notes are design requirements, not proof of safety.

## Keep-out conditions

- Operate only on a flat, clear, bounded test floor under direct adult/maker supervision.
- Keep away from stairs, table edges, roads, wet areas, food, children, and pets.
- Keep hands, hair, clothing, loose cables, and tools clear of servo linkages while powered.
- Remove the battery and unload servo joints before rewiring, adjusting horns, or working on the frame.
- Do not lift or carry the robot by its legs; do not attach a payload until its mounts and structural limits are tested.

## Power and battery

- Use only a compatible battery and matching charger with intact insulation and connectors; follow their actual manufacturer datasheets.
- Never charge unattended, puncture, crush, short, reverse, or solder directly to loose lithium cells.
- Add an appropriately rated fuse near the battery source; verify regulator, wiring, connector, and switch ratings for measured servo stall transients.
- Keep logic power distinct from high-current servo power and establish the correct shared signal ground.
- Measure rail sag, heating, and current during bench tests. Stop if any component becomes hot, the pack swells, insulation softens, or the controller resets.

## Autonomous-mode constraints

- Autonomy remains disabled by default until an actual stop/disable control, board adapter, wiring map, sensor validation, and short-burst gait adapter exist.
- Invalid, stale, disconnected, or implausible critical sensor data must result in a stop, not a guess that the route is safe.
- A low-cost reflectance sensor cannot certify the edge of stairs or reliably recognize every floor. The robot is **not** certified for use near stairs.
- Every motion remains a short, interruptible command. Include physical battery isolation as the final fallback; firmware alone cannot guarantee stopping a failed servo or power stage.
- Emergency stop and fault reset must be exercised physically with the robot supported before any walking test.

## Test documentation

Use the checklist in [`TEST_PLAN.md`](TEST_PLAN.md). Record setup, surface, thresholds, failures, and repetitions. A successful demo under one set of conditions is not a general safety guarantee.
