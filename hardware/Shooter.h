#ifndef SHOOTER_H
#define SHOOTER_H

#include "Talon.h"
#include "Encoder.h"
#include "../SimplePID.h"
#include "TaskSubsystem.h"

class Shooter : public TaskSubsystem {
  Talon *motor;
  Encoder *sensor;

  SimplePID *pid;
  SimplePID::PIDSnapshot snapshot;

  public:
    Shooter();
    ~Shooter();

    void setRaw(double speed);
    void setRate(double speed);
    SimplePID *getPID();
    double getRate();
    void getPIDSnapshot(SimplePID::PIDSnapshot *copy);

    void update();
};

#endif
