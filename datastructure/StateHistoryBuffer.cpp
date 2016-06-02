#include "StateHistoryBuffer.h"
#include "stdio.h"
#include "strlib.h"
#include "math.h"
#include "stdLib.h"

StateHistoryBuffer::StateHistoryBuffer(int size) {
  space = (RobotStateMessage*)malloc(sizeof(RobotStateMessage)*size);
  insertAt = 0;
  readAt = 0;
  len = size;
  mutex = semMCreate(SEM_Q_FIFO);
}

void StateHistoryBuffer::insert(RobotStateMessage *msg) {
  semTake(mutex, WAIT_FOREVER);
  if ( insertAt%len == readAt ) {
    readAt++;
    if ( readAt == len )
      readAt = 0;
  }
  memcpy(&space[insertAt], msg, sizeof(RobotStateMessage));
  insertAt = (insertAt+1)%len;
  semGive(mutex);
}

RobotStateMessage StateHistoryBuffer::stateAt(double ts) {
  RobotStateMessage *msg = NULL;
  RobotStateMessage *prev = NULL;
  double dT = 999.0;

  semTake(mutex, WAIT_FOREVER);
  do {
    msg = &space[readAt];
    if ( fabs(ts-msg->ts) < dT )
    {
      dT = fabs(ts-msg->ts);
    }
    else {
      msg = prev;
      break;
    }
    prev = msg;
    readAt = (readAt+1)%len;
  } while ( readAt != insertAt );
  if ( msg == NULL )
  {
    semGive(mutex);
    RobotStateMessage dummy;
    bzero((char*)&dummy, sizeof(RobotStateMessage));
    return dummy;
  }

  RobotStateMessage copy = *msg;
  semGive(mutex);
  return copy;
}
