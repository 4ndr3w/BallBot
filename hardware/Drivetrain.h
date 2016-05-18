#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "Talon.h"
#include "Encoder.h"

class Drivetrain {
public:
  enum DriveMode { RAW, PID_DISTANCE, PID_ANGLE, PROFILE };
private:
  Talon *left;
  Talon *right;

  Encoder *leftEncoder;
  Encoder *rightEncoder;

  DriveMode mode;

  public:

    Drivetrain();
    ~Drivetrain();

    void set(double left, double right);
    double getLeft();
    double getRight();
};

#endif
