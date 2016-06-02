#include "Robot.h"

Robot::Robot() {
  //history = new StateHistoryBuffer(10);

  drivetrain = new Drivetrain();
  shooter = new Shooter();
  intake = new Intake();
}
