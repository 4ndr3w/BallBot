#ifndef RobotStateMessage_h
#define RobotStateMessage_h

#include "SimplePID.h"

struct RobotStateMessage {
  double ts;
  SimplePID::PIDSnapshot shooter;
  int16_t intakeState;
  double yaw;
};

#endif
