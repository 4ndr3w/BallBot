#include "Drivetrain.h"
#include "PortMap.h"
#include "math.h"


extern Robot* robot;

Drivetrain::Drivetrain() : mode(PID_ANGLE) {
  left = new Talon(LEFT_DRIVE_PWM);
  right = new Talon(RIGHT_DRIVE_PWM);

  leftEncoder = new Encoder(LEFT_ENCODER_A_DIGITAL, LEFT_ENCODER_B_DIGITAL, true);
  rightEncoder = new Encoder(RIGHT_ENCODER_A_DIGITAL, RIGHT_ENCODER_B_DIGITAL, false);

  gyro = new BNO055();

  leftEncoder->Start();
  rightEncoder->Start();

  left->Set(0);
  right->Set(0);

  turnPID = new SimplePID(0.05,0.007,0,0);
  turnPID->setContinous(360);
  startUpdateTask("Drivetrain");
}

Drivetrain::~Drivetrain() {
  left->Set(0);
  right->Set(0);

  leftEncoder->Stop();
  rightEncoder->Stop();

  delete left;
  delete right;
  delete leftEncoder;
  delete rightEncoder;
}

void Drivetrain::setState(DriveMode mode)
{
  this->mode = mode;
}

void Drivetrain::set(double left, double right) {
  lock();
  this->left->Set(left);
  this->right->Set(right);
  unlock();
}

double Drivetrain::getLeft() {
  return leftEncoder->Get();
}

double Drivetrain::getRight() {
  return rightEncoder->Get();
}

double Drivetrain::getAngle() {
  return gyro->getYaw();
}

SimplePID *Drivetrain::getTurnPID() {
  return turnPID;
}

void Drivetrain::update() {
  SimplePID::PIDSnapshot snapshot;
  if ( mode == PID_ANGLE ) {
    double speed = turnPID->calculate(getAngle(), &snapshot)/3;
    printf("cur: %2.4f error %2.4f out %2.4f\n", snapshot.input, snapshot.error, snapshot.out);

    set(speed, speed);
  }
}
