#include "KestrelCore.h"

#include <cmath>

namespace kestrel {

const float BehaviorCore::kMaxTiltDegrees = 25.0f;

Inputs::Inputs()
    : nowMs(0),
      missionEnabled(false),
      emergencyStop(false),
      resetFault(false),
      frontValid(false),
      frontSampleMs(0),
      frontMm(0),
      leftScanValid(false),
      leftSampleMs(0),
      leftMm(0),
      rightScanValid(false),
      rightSampleMs(0),
      rightMm(0),
      leftFloorValid(false),
      leftFloorSampleMs(0),
      leftFloorPresent(false),
      rightFloorValid(false),
      rightFloorSampleMs(0),
      rightFloorPresent(false),
      imuValid(false),
      imuSampleMs(0),
      rollDegrees(0.0f),
      pitchDegrees(0.0f),
      bumperPressed(false) {}

BehaviorCore::BehaviorCore()
    : mode_(Mode::Idle), fault_(Fault::None), turnAction_(Action::TurnLeft),
      actionStartedMs_(0) {}

bool BehaviorCore::criticalSensorsFresh(const Inputs& input) const {
  const bool frontFresh = input.frontValid &&
      static_cast<uint32_t>(input.nowMs - input.frontSampleMs) <=
          kMaxCriticalSampleAgeMs;
  const bool imuFresh = input.imuValid &&
      static_cast<uint32_t>(input.nowMs - input.imuSampleMs) <=
          kMaxCriticalSampleAgeMs;
  const bool leftFloorFresh = input.leftFloorValid &&
      static_cast<uint32_t>(input.nowMs - input.leftFloorSampleMs) <=
          kMaxCriticalSampleAgeMs;
  const bool rightFloorFresh = input.rightFloorValid &&
      static_cast<uint32_t>(input.nowMs - input.rightFloorSampleMs) <=
          kMaxCriticalSampleAgeMs;
  return frontFresh && imuFresh && leftFloorFresh && rightFloorFresh;
}

bool BehaviorCore::sideScansFresh(const Inputs& input) const {
  const bool leftFresh = input.leftScanValid &&
      static_cast<uint32_t>(input.nowMs - input.leftSampleMs) <=
          kMaxSideSampleAgeMs;
  const bool rightFresh = input.rightScanValid &&
      static_cast<uint32_t>(input.nowMs - input.rightSampleMs) <=
          kMaxSideSampleAgeMs;
  return leftFresh && rightFresh;
}

bool BehaviorCore::safeToReset(const Inputs& input) const {
  if (input.missionEnabled || input.emergencyStop || input.bumperPressed ||
      !criticalSensorsFresh(input)) {
    return false;
  }
  if (!input.leftFloorPresent || !input.rightFloorPresent ||
      !std::isfinite(input.rollDegrees) || !std::isfinite(input.pitchDegrees)) {
    return false;
  }
  return std::fabs(input.rollDegrees) <= kMaxTiltDegrees &&
         std::fabs(input.pitchDegrees) <= kMaxTiltDegrees;
}

Output BehaviorCore::makeOutput(Action action, const char* reason) const {
  Output output;
  output.mode = mode_;
  output.action = action;
  output.fault = fault_;
  output.reason = reason;
  return output;
}

Output BehaviorCore::latchFault(Fault fault, const char* reason) {
  mode_ = Mode::Fault;
  fault_ = fault;
  return makeOutput(Action::Stop, reason);
}

Output BehaviorCore::chooseNextAction(const Inputs& input) {
  if (input.frontMm >= kObstacleStopMm) {
    mode_ = Mode::MoveBurst;
    actionStartedMs_ = input.nowMs;
    return makeOutput(Action::StepForward, "short forward burst; recheck sensors next");
  }

  if (!sideScansFresh(input)) {
    mode_ = Mode::Blocked;
    actionStartedMs_ = input.nowMs;
    return makeOutput(Action::Stop, "obstacle ahead; waiting for fresh side scan");
  }

  const bool leftClear = input.leftMm >= kSideClearMm;
  const bool rightClear = input.rightMm >= kSideClearMm;
  if (!leftClear && !rightClear) {
    mode_ = Mode::Blocked;
    actionStartedMs_ = input.nowMs;
    return makeOutput(Action::Stop, "no side route meets clearance threshold");
  }

  mode_ = Mode::TurnBurst;
  actionStartedMs_ = input.nowMs;
  if (leftClear && (!rightClear || input.leftMm >= input.rightMm)) {
    turnAction_ = Action::TurnLeft;
    return makeOutput(Action::TurnLeft, "short turn toward clearer side");
  }
  turnAction_ = Action::TurnRight;
  return makeOutput(Action::TurnRight, "short turn toward clearer side");
}

Output BehaviorCore::update(const Inputs& input) {
  if (fault_ != Fault::None) {
    if (input.resetFault && safeToReset(input)) {
      fault_ = Fault::None;
      mode_ = Mode::Idle;
      actionStartedMs_ = input.nowMs;
      return makeOutput(Action::Stop, "fault reset; remain stopped until re-armed");
    }
    mode_ = Mode::Fault;
    return makeOutput(Action::Stop, "fault latched; reset only while disarmed and safe");
  }

  if (input.emergencyStop) {
    return latchFault(Fault::EmergencyStop, "emergency stop latched");
  }
  if (input.bumperPressed) {
    return latchFault(Fault::BumperPressed, "bumper pressed; motion stopped");
  }
  if ((input.leftFloorValid && !input.leftFloorPresent) ||
      (input.rightFloorValid && !input.rightFloorPresent)) {
    return latchFault(Fault::EdgeDetected, "possible floor edge; motion stopped");
  }
  if (input.imuValid &&
      (!std::isfinite(input.rollDegrees) || !std::isfinite(input.pitchDegrees) ||
       std::fabs(input.rollDegrees) > kMaxTiltDegrees ||
       std::fabs(input.pitchDegrees) > kMaxTiltDegrees)) {
    return latchFault(Fault::ExcessiveTilt, "excessive tilt; motion stopped");
  }

  if (!input.missionEnabled) {
    mode_ = Mode::Idle;
    actionStartedMs_ = input.nowMs;
    return makeOutput(Action::Stop, "mission disabled");
  }

  if (!criticalSensorsFresh(input) ||
      !std::isfinite(input.rollDegrees) || !std::isfinite(input.pitchDegrees)) {
    return latchFault(Fault::StaleOrInvalidSensor,
                      "critical sensor invalid or stale; motion stopped");
  }

  if (mode_ == Mode::MoveBurst) {
    if (input.frontMm < kObstacleStopMm) {
      mode_ = Mode::Idle;
      actionStartedMs_ = input.nowMs;
      return makeOutput(Action::Stop, "obstacle entered during burst; stop and re-evaluate");
    }
    if (static_cast<uint32_t>(input.nowMs - actionStartedMs_) < kMoveBurstMs) {
      return makeOutput(Action::StepForward, "forward burst in progress");
    }
    mode_ = Mode::Idle;
    actionStartedMs_ = input.nowMs;
    return makeOutput(Action::Stop, "forward burst complete; recheck before next action");
  }

  if (mode_ == Mode::TurnBurst) {
    if (static_cast<uint32_t>(input.nowMs - actionStartedMs_) < kTurnBurstMs) {
      return makeOutput(turnAction_, "turn burst in progress");
    }
    mode_ = Mode::Idle;
    actionStartedMs_ = input.nowMs;
    return makeOutput(Action::Stop, "turn burst complete; recheck before next action");
  }

  if (mode_ == Mode::Blocked) {
    if (static_cast<uint32_t>(input.nowMs - actionStartedMs_) < kBlockedPauseMs) {
      return makeOutput(Action::Stop, "blocked; pause before another decision");
    }
    mode_ = Mode::Idle;
  }

  return chooseNextAction(input);
}

}  // namespace kestrel
