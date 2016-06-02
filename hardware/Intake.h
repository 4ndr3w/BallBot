#ifndef INTAKE_H
#define INTAKE_H

#include "Talon.h"
#include "Counter.h"
#include "TaskSubsystem.h"

#define INTAKE_ROLLIN_SPEED 0.4
#define INTAKE_ROLLOUT_SPEED -0.4

class Intake : public TaskSubsystem {
  Talon *roller;
  Counter *ballSensor;
public:

  enum IntakeState { OFF, WANT, HAS, SHOOT, EJECT, MANUAL_ROLLIN, MANUAL_ROLLOUT };

  Intake();
  bool hasBall();
  void setState(IntakeState newState);
  IntakeState getState();
  void update();

private:
  IntakeState state;
};

#endif
