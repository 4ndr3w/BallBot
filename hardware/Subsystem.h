#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

#include "semLib.h"

class Subsystem {
  int taskId;
  SEM_ID mutex;
protected:
  void startUpdateTask(char* description);
public:
  Subsystem();
  void lock();
  void unlock();
  virtual void update() = 0;
};

#endif
