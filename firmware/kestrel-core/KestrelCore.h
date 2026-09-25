#pragma once

#include <cstdint>

namespace kestrel {

enum class Mode : uint8_t {
  Idle,
  MoveBurst,
  TurnBurst,
  Blocked,
  Fault
};

enum class Action : uint8_t {
  Stop,
  StepForward,
  TurnLeft,
  TurnRight
};

enum class Fault : uint8_t {
  None,
  EmergencyStop,
  EdgeDetected,
  BumperPressed,
  ExcessiveTilt,
  StaleOrInvalidSensor
};

// Sensor sample timestamps are uint32 millis() values. Age checks use unsigned
// subtraction, so normal millis() rollover is supported.
struct Inputs {
  uint32_t nowMs;
  bool missionEnabled;
  bool emergencyStop;
  bool resetFault;

  bool frontValid;
  uint32_t frontSampleMs;
  uint16_t frontMm;

  bool leftScanValid;
  uint32_t leftSampleMs;
  uint16_t leftMm;
  bool rightScanValid;
  uint32_t rightSampleMs;
  uint16_t rightMm;

  bool leftFloorValid;
  uint32_t leftFloorSampleMs;
  bool leftFloorPresent;
  bool rightFloorValid;
  uint32_t rightFloorSampleMs;
  bool rightFloorPresent;

  bool imuValid;
  uint32_t imuSampleMs;
  float rollDegrees;
  float pitchDegrees;

  bool bumperPressed;

  Inputs();
};

struct Output {
  Mode mode;
  Action action;
  Fault fault;
  const char* reason;
};

// A deterministic high-level supervisor. It does not generate servo angles,
// gait frames, or motor PWM. The board-specific adapter must map these short
// actions to calibrated, interruptible Sesame motions.
class BehaviorCore {
 public:
  BehaviorCore();
  Output update(const Inputs& input);

  Mode mode() const { return mode_; }
  Fault fault() const { return fault_; }

  static const uint16_t kObstacleStopMm = 350;
  static const uint16_t kSideClearMm = 450;
  static const uint32_t kMaxCriticalSampleAgeMs = 300;
  static const uint32_t kMaxSideSampleAgeMs = 500;
  static const uint32_t kMoveBurstMs = 250;
  static const uint32_t kTurnBurstMs = 250;
  static const uint32_t kBlockedPauseMs = 400;
  static const float kMaxTiltDegrees;

 private:
  Mode mode_;
  Fault fault_;
  Action turnAction_;
  uint32_t actionStartedMs_;

  bool criticalSensorsFresh(const Inputs& input) const;
  bool sideScansFresh(const Inputs& input) const;
  bool safeToReset(const Inputs& input) const;
  Output makeOutput(Action action, const char* reason) const;
  Output latchFault(Fault fault, const char* reason);
  Output chooseNextAction(const Inputs& input);
};

}  // namespace kestrel
