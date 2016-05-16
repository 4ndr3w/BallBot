#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include "Talon.h"
#include "Encoder.h"

class Drivetrain {
  Talon *left;
  Talon *right;

  Encoder *leftEncoder;
  Encoder *rightEncoder;

  public:
    Drivetrain();
    ~Drivetrain();

    void set(double left, double right);
    double getLeft();
    double getRight();
};

#endif
