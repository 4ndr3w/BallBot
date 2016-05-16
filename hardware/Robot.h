#ifndef ROBOT_H
#define ROBOT_H

#include "Drivetrain.h"
#include "Shooter.h"
#include "Intake.h"

class Robot {
  public:
    Robot();

    Drivetrain *drivetrain;
    Shooter *shooter;
    Intake *intake;
};

extern Robot* robot;

#endif
