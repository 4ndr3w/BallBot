#ifndef ROBOT_H
#define ROBOT_H

#include "Drivetrain.h"
#include "Shooter.h"
#include "Intake.h"
#include "../datastructure/StateHistoryBuffer.h"


class Robot {
  public:
    Robot();

    Drivetrain *drivetrain;
    Shooter *shooter;
    Intake *intake;
    //StateHistoryBuffer *history;
};

#endif
