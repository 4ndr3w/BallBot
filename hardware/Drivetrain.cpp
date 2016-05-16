#include "Drivetrain.h"
#include "PortMap.h"

Drivetrain::Drivetrain() {
  left = new Talon(LEFT_DRIVE_PWM);
  right = new Talon(RIGHT_DRIVE_PWM);

  leftEncoder = new Encoder(LEFT_ENCODER_A_DIGITAL, LEFT_ENCODER_B_DIGITAL, true);
  rightEncoder = new Encoder(RIGHT_ENCODER_A_DIGITAL, RIGHT_ENCODER_B_DIGITAL, false);

  leftEncoder->Start();
  rightEncoder->Start();

  left->Set(0);
  right->Set(0);
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

void Drivetrain::set(double left, double right) {
  this->left->Set(left);
  this->right->Set(right);
}

double Drivetrain::getLeft() {
  return leftEncoder->Get();
}

double Drivetrain::getRight() {
  return rightEncoder->Get();
}
