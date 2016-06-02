#include "stdint.h"

#ifndef RobotControlMessage_h
#define RobotControlMessage_h

struct RobotControlMessage {
  char messageType;
  char reserved[127];
};

struct RobotControlMessage_SetDriveState {
  char messageType;
  uint8_t state;
  char reserved[125];
};

struct RobotControlMessage_SetDriveSetpoint {
  char messageType;
  double setpoint;
  char reserved[119];
};

struct RobotControlMessage_SetDriveRaw {
  char messageType;
  double left;
  double right;
  char reserved[111];
};


struct RobotControlMessage_SetIntakeState {
  char messageType;
  uint8_t state;
  char reserved[125];
};

#endif
