#include "SimplePID.h"
#include "Timer.h"
#include "math.h"

SimplePID::SimplePID(double kP, double kI, double kD, double kF) :
  setpoint(0), error(0), lastT(0), errSum(0), prevInput(0),
  minOut(-1), maxOut(1) {
  this->kP = kP;
  this->kI = kI;
  this->kD = kD;
  this->kF = kF;
}

void SimplePID::setSetpoint(double setpoint) {
  this->setpoint = setpoint;
}

double SimplePID::getSetpoint() {
  return setpoint;
}

double SimplePID::getError() {
  return error;
}

double SimplePID::getErrSum() {
  return errSum;
}

bool SimplePID::isStable(double allowed) {
  return fabs(error) < allowed;
}

void SimplePID::reset(double initialPosition) {
  lastT = Timer::GetPPCTimestamp();
  prevInput = initialPosition;
  errSum = 0;
}

double SimplePID::calculate(double input, PIDSnapshot *snapshot) {
  double now = Timer::GetPPCTimestamp();
  double dT = now-lastT;

  error = setpoint-input;

  errSum += error*dT;

  double deltaPos = (input-prevInput);

  lastT = now;
  prevInput = input;

  double pContrib = kP*error;
  double iContrib = kI*errSum;
  double dContrib = kD*(deltaPos/dT);
  double fContrib = kF*setpoint;

  double out = pContrib + iContrib - dContrib + fContrib;

  if ( snapshot != NULL )
  {
    snapshot->error = error;
    snapshot->setpoint = setpoint;
    snapshot->input = input;

    snapshot->p = pContrib;
    snapshot->i = iContrib;
    snapshot->d = dContrib;

    snapshot->f = fContrib;

    snapshot->out = out;
  }

  return out;
}
