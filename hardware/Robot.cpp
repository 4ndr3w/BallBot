#include "Robot.h"

Robot::Robot() {
  drivetrain = new Drivetrain();
  shooter = new Shooter();
  intake = new Intake();
}
