#ifndef INTAKE_H
#define INTAKE_H

#include "Talon.h"
#include "DigitalInput.h"
#include "Subsystem.h"

#define INTAKE_ROLLIN_SPEED 0.4
#define INTAKE_ROLLOUT_SPEED -0.4

class Intake : public Subsystem {
  Talon *roller;
  DigitalInput *ballSensor;
  double manualSpeed;
public:

  enum IntakeState { OFF, WANT, HAS, SHOOT, EJECT, MANUAL_ROLLIN, MANUAL_ROLLOUT };

  Intake();
  bool hasBall();
  void setState(IntakeState newState);

  void update();

private:
  IntakeState state;
};

#endif
