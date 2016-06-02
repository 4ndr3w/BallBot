#ifndef STATEHISTORYBUFFER_H
#define STATEHISTORYBUFFER_H

#include "RobotStateMessage.h"
#include "semLib.h"

class StateHistoryBuffer {
  SEM_ID mutex;
  RobotStateMessage *space;
  int insertAt;
  int readAt;
  int len;
  public:
    StateHistoryBuffer(int size);
    void insert(RobotStateMessage *msg);
    RobotStateMessage stateAt(double ts);
};

#endif
