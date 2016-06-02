#include "SimplePID.h"
#include "Timer.h"
#include "math.h"

SimplePID::SimplePID(double kP, double kI, double kD, double kF) :
  setpoint(0), error(0), lastT(0), errSum(0), prevError(0),
  minOut(-1), maxOut(1), maxInput(0), continous(false) {
  this->kP = kP;
  this->kI = kI;
  this->kD = kD;
  this->kF = kF;
}

void SimplePID::setContinous(double maxInput) {
  this->continous = true;
  this->maxInput = maxInput;
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

void SimplePID::reset() {
  lastT = Timer::GetPPCTimestamp();
  prevError = 0;
  errSum = 0;
}

double SimplePID::calculate(double input, PIDSnapshot *snapshot) {
  double now = Timer::GetPPCTimestamp();
  double dT = now-lastT;

  error = setpoint-input;

  if ( continous && fabs(error) > (maxInput/2) )
	{
			if ( error > 0 )
			   error = error - maxInput;
			else
			   error = error + maxInput;
	}

  errSum += error*dT;

  double deltaPos = (error-prevError);

  lastT = now;
  prevError = error;

  double pContrib = kP*error;
  double iContrib = kI*errSum;
  double dContrib = kD*(deltaPos/dT);
  double fContrib = kF*setpoint;

  double out = pContrib + iContrib + dContrib + fContrib;

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
