#include "Shooter.h"
#include "../PortMap.h"

Shooter::Shooter() {
  motor = new Talon(SHOOTER_PWM);
  sensor = new Encoder(SHOOTER_ENCODER_A, SHOOTER_ENCODER_B, false, Encoder::k1X);
  sensor->SetDistancePerPulse(1.0/SHOOTER_ENCODER_CPR);
  sensor->Start();
  motor->Set(0);

  pid = new SimplePID(0, 0, 0, 0);
}

void Shooter::setRaw(double raw) {
  motor->Set(raw);
}

void Shooter::setRate(double setpoint) {

}

double Shooter::getRate() {
  return sensor->GetRate();
}

double Shooter::getRevs()
{
  return sensor->GetDistance();
}
