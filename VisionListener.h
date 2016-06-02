#include "datastructure/VisionMessage.h"
#include "semLib.h"

#ifndef VISIONLISTENER_H
#define VISIONLISTENER_H

class VisionListener {
  int sock;
  int taskId;
  SEM_ID mutex;
  VisionMessage msg;
public:
  VisionListener(int port);
  void handle();
  VisionMessage getNewestMessage();
};


#endif
