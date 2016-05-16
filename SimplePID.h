#ifndef SIMPLEPID_H
#define SIMPLEPID_H

#include "stdint.h"

struct PIDSnapshot {
  uint32_t error;
  uint32_t setpoint;
  uint32_t p;
  uint32_t i;
  uint32_t d;
  uint32_t f;
};

class SimplePID {
  double kP, kI, kD, kF;
  double setpoint;
  double error;

  double lastT;

  double errSum;
  double prevInput;

  double minOut, maxOut;

  public:
    SimplePID(double kP, double kI, double kD, double kF);
    double calculate(double input);
    double getError();
    bool isStable(double allowed);
    void setSetpoint(double setpoint);
    void reset(double initialPosition);


};

#endif
