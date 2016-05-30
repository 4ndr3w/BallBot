#include "Shooter.h"
#include "../PortMap.h"

Shooter::Shooter() {
  motor = new Talon(SHOOTER_PWM);
  sensor = new Encoder(SHOOTER_ENCODER_A, SHOOTER_ENCODER_B, false, Encoder::k1X);
  sensor->SetDistancePerPulse(1.0/SHOOTER_ENCODER_CPR);
  sensor->Start();
  motor->Set(0);

  pid = new SimplePID(0.04, 0.01, 0, 0.01029411);
  pid->setSetpoint(0);

  startUpdateTask("Shooter");
}

void Shooter::setRaw(double raw) {
  motor->Set(raw);
}

void Shooter::setRate(double setpoint) {
  lock();
  pid->setSetpoint(setpoint);
  unlock();
}

double Shooter::getRate() {
  return sensor->GetRate();
}

void Shooter::getPIDSnapshot(SimplePID::PIDSnapshot *copy) {
  lock();
  memcpy(copy, &snapshot, sizeof(SimplePID::PIDSnapshot));
  unlock();
}

SimplePID* Shooter::getPID() {
  return pid;
}

void Shooter::update() {
  double result = pid->calculate(getRate(), &snapshot);
  if ( result < 0 )
    result = 0;
//  printf("output %2.4f\n", result);
  motor->Set(-result);
}
