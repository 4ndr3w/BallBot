#ifndef SIMPLEPID_H
#define SIMPLEPID_H

#include "stdint.h"

class SimplePID {
  double kP, kI, kD, kF;
  double setpoint;
  double error;

  double lastT;

  double errSum;
  double prevError;

  double minOut, maxOut;

  double maxInput;
  bool continous;
  public:
      struct PIDSnapshot {
        float error;
        float setpoint;
        float input;

        float p;
        float i;
        float d;
        float f;

        float out;
      };

    SimplePID(double kP, double kI, double kD, double kF);
    double calculate(double input, PIDSnapshot *snapshot);
    double getError();
    void setContinous(double maxInput);
    bool isStable(double allowed);
    void setSetpoint(double setpoint);
    double getSetpoint();
    void reset();

    double getErrSum();


};

#endif
