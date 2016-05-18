#include "Intake.h"
#include "PortMap.h"
#include "Timer.h"

Intake::Intake() : state(OFF)
{
  roller = new Talon(INTAKE_PWM);
  ballSensor = new DigitalInput(BALL_SENSOR);
  startUpdateTask("Intake");
}

bool Intake::hasBall()
{
  return ballSensor->Get();
}

Intake::IntakeState Intake::getState()
{
  return state;
}

void Intake::setState(IntakeState newState)
{
  lock();
  if ( newState != state )
    printf("Intake: State changed to %i\n", newState);

  state = newState;
  unlock();
}

void Intake::update()
{
  switch (state) {
    case OFF:
    {
      roller->Set(0);
      break;
    }

    case WANT:
    {
      if ( !ballSensor->Get() )
      {
        roller->Set(0);
        state = HAS;
      }
      else {
        roller->Set(INTAKE_ROLLIN_SPEED);
      }
      break;
    }

    case HAS:
    {
      roller->Set(0);
      break;
    }

    case SHOOT:
    {
      roller->Set(INTAKE_ROLLIN_SPEED);
      Wait(1.0);
      roller->Set(0);
      state = OFF;
      break;
    }

    case EJECT:
    {
      roller->Set(INTAKE_ROLLOUT_SPEED);
      Wait(1.0);
      roller->Set(0);
      state = OFF;
    }

    case MANUAL_ROLLIN:
    {
      roller->Set(INTAKE_ROLLIN_SPEED);
      break;
    }

    case MANUAL_ROLLOUT:
    {
      roller->Set(INTAKE_ROLLOUT_SPEED);
      break;
    }
  }
}
