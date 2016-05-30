#ifndef ROBOT_H
#define ROBOT_H

#include "Drivetrain.h"
#include "Shooter.h"
#include "Intake.h"
#include "BNO055.h"

class Robot {
  public:
    Robot();

    Drivetrain *drivetrain;
    Shooter *shooter;
    Intake *intake;
    BNO055 *gyro;
};

extern Robot* robot;

#endif
