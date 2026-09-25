#include "../KestrelCore.h"

#include <cassert>
#include <cmath>
#include <iostream>

using kestrel::Action;
using kestrel::BehaviorCore;
using kestrel::Fault;
using kestrel::Inputs;
using kestrel::Mode;

static Inputs safeInputs() {
  Inputs in;
  in.nowMs = 1000;
  in.missionEnabled = true;
  in.frontValid = true;
  in.frontSampleMs = 1000;
  in.frontMm = 1000;
  in.leftScanValid = true;
  in.leftSampleMs = 1000;
  in.leftMm = 800;
  in.rightScanValid = true;
  in.rightSampleMs = 1000;
  in.rightMm = 700;
  in.leftFloorValid = true;
  in.leftFloorSampleMs = 1000;
  in.leftFloorPresent = true;
  in.rightFloorValid = true;
  in.rightFloorSampleMs = 1000;
  in.rightFloorPresent = true;
  in.imuValid = true;
  in.imuSampleMs = 1000;
  return in;
}

static void refreshCritical(Inputs& in) {
  in.frontSampleMs = in.nowMs;
  in.imuSampleMs = in.nowMs;
  in.leftFloorSampleMs = in.nowMs;
  in.rightFloorSampleMs = in.nowMs;
}

static void testShortForwardBurstAndStop() {
  BehaviorCore core;
  Inputs in = safeInputs();
  assert(core.update(in).action == Action::StepForward);

  in.nowMs = 1249;
  refreshCritical(in);
  assert(core.update(in).action == Action::StepForward);

  in.nowMs = 1250;
  refreshCritical(in);
  const auto out = core.update(in);
  assert(out.action == Action::Stop);
  assert(out.mode == Mode::Idle);
}

static void testObstacleChoosesClearerSide() {
  BehaviorCore core;
  Inputs in = safeInputs();
  in.frontMm = 200;
  in.leftMm = 600;
  in.rightMm = 1100;
  const auto out = core.update(in);
  assert(out.action == Action::TurnRight);
  assert(out.mode == Mode::TurnBurst);
  assert(out.fault == Fault::None);

  in.nowMs += 100;
  refreshCritical(in);
  const auto duringTurn = core.update(in);
  assert(duringTurn.action == Action::TurnRight);
  assert(duringTurn.mode == Mode::TurnBurst);

  in.nowMs += BehaviorCore::kTurnBurstMs;
  refreshCritical(in);
  const auto afterTurn = core.update(in);
  assert(afterTurn.action == Action::Stop);
  assert(afterTurn.mode == Mode::Idle);
}

static void testObstacleInterruptsForwardBurst() {
  BehaviorCore core;
  Inputs in = safeInputs();
  assert(core.update(in).action == Action::StepForward);

  in.nowMs += 50;
  refreshCritical(in);
  in.frontMm = 200;
  auto out = core.update(in);
  assert(out.action == Action::Stop);
  assert(out.mode == Mode::Idle);

  in.nowMs += 1;
  refreshCritical(in);
  out = core.update(in);
  assert(out.action == Action::TurnLeft);
  assert(out.mode == Mode::TurnBurst);
}

static void testNoClearRouteStops() {
  BehaviorCore core;
  Inputs in = safeInputs();
  in.frontMm = 200;
  in.leftMm = 300;
  in.rightMm = 400;
  const auto out = core.update(in);
  assert(out.action == Action::Stop);
  assert(out.mode == Mode::Blocked);
}

static void testEdgeFaultLatchesUntilSafeDisarmedReset() {
  BehaviorCore core;
  Inputs in = safeInputs();
  in.rightFloorPresent = false;
  auto out = core.update(in);
  assert(out.action == Action::Stop);
  assert(out.fault == Fault::EdgeDetected);

  in.nowMs += 10;
  refreshCritical(in);
  in.rightFloorPresent = true;
  in.resetFault = true;
  in.missionEnabled = true;
  out = core.update(in);
  assert(out.mode == Mode::Fault);
  assert(out.action == Action::Stop);

  in.missionEnabled = false;
  out = core.update(in);
  assert(out.mode == Mode::Idle);
  assert(out.fault == Fault::None);
  assert(out.action == Action::Stop);
}

static void testEmergencyStopLatches() {
  BehaviorCore core;
  Inputs in = safeInputs();
  in.emergencyStop = true;
  auto out = core.update(in);
  assert(out.fault == Fault::EmergencyStop);
  assert(out.action == Action::Stop);

  in.emergencyStop = false;
  in.missionEnabled = false;
  in.resetFault = true;
  in.nowMs += 20;
  refreshCritical(in);
  out = core.update(in);
  assert(out.fault == Fault::None);
  assert(out.mode == Mode::Idle);
}

static void testStaleCriticalSensorFailsClosed() {
  BehaviorCore core;
  Inputs in = safeInputs();
  in.nowMs += BehaviorCore::kMaxCriticalSampleAgeMs + 1;
  refreshCritical(in);
  in.frontSampleMs = 1000;
  const auto out = core.update(in);
  assert(out.fault == Fault::StaleOrInvalidSensor);
  assert(out.action == Action::Stop);
}

static void testStaleFloorSensorFailsClosed() {
  BehaviorCore core;
  Inputs in = safeInputs();
  in.nowMs += BehaviorCore::kMaxCriticalSampleAgeMs + 1;
  refreshCritical(in);
  in.rightFloorSampleMs = 1000;
  const auto out = core.update(in);
  assert(out.fault == Fault::StaleOrInvalidSensor);
  assert(out.action == Action::Stop);
}

static void testTiltFaultAndNan() {
  BehaviorCore core;
  Inputs in = safeInputs();
  in.pitchDegrees = 26.0f;
  auto out = core.update(in);
  assert(out.fault == Fault::ExcessiveTilt);
  assert(out.action == Action::Stop);

  BehaviorCore second;
  in = safeInputs();
  in.rollDegrees = std::nanf("");
  out = second.update(in);
  assert(out.fault == Fault::ExcessiveTilt);
  assert(out.action == Action::Stop);
}

int main() {
  testShortForwardBurstAndStop();
  testObstacleChoosesClearerSide();
  testObstacleInterruptsForwardBurst();
  testNoClearRouteStops();
  testEdgeFaultLatchesUntilSafeDisarmedReset();
  testEmergencyStopLatches();
  testStaleCriticalSensorFailsClosed();
  testStaleFloorSensorFailsClosed();
  testTiltFaultAndNan();
  std::cout << "All KESTREL core tests passed.\n";
  return 0;
}
