#include "Robot.h"

#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "Talon.h"
#include "Encoder.h"
#include "TaskSubsystem.h"
#include "../BNO055.h"
#include "../SimplePID.h"

class Drivetrain : public TaskSubsystem {
public:
  enum DriveMode { RAW, PID_DISTANCE, PID_ANGLE, PROFILE };
private:
  Talon *left;
  Talon *right;

  Encoder *leftEncoder;
  Encoder *rightEncoder;

  DriveMode mode;

  BNO055 *gyro;
  SimplePID *turnPID;

  public:

    Drivetrain();
    ~Drivetrain();

    void setState(DriveMode mode);
    void set(double left, double right);
    double getLeft();
    double getRight();
    double getAngle();
    SimplePID *getTurnPID();
    void update();
};

#endif
