#ifndef SHOOTER_H
#define SHOOTER_H

#include "Talon.h"
#include "Encoder.h"
#include "../SimplePID.h"

class Shooter {
  Talon *motor;
  Encoder *sensor;

  SimplePID *pid;

  public:
    Shooter();
    ~Shooter();

    void setRaw(double speed);
    void setRate(double speed);
    double getRate();
    double getRevs();
};

#endif
