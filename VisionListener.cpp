#include "VisionListener.h"
#include "sockLib.h"
#include "taskLib.h"
#include "inetLib.h"
#include "strLib.h"
#include "stdio.h"

void spawnVisionListener(void* ptr)
{
  ((VisionListener*)ptr)->handle();
}

VisionListener::VisionListener(int port) {
  msg.theta = 0;
  mutex = semMCreate(SEM_Q_FIFO);

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  sockaddr_in bindaddr;
  int sockaddr_len = sizeof(sockaddr_in);
  bzero((char*)&bindaddr, sockaddr_len);
  bindaddr.sin_family = AF_INET;
  bindaddr.sin_port = htons(port);
  bindaddr.sin_addr.s_addr = INADDR_ANY;
  bindaddr.sin_len = sockaddr_len;

  if ( bind(sock, (sockaddr*)&bindaddr, sockaddr_len) == ERROR ) {
    close(sock);
    perror("bind() failed");
    return;
  }
  printf("Starting VisionListener\n");
  taskId = taskSpawn("VisionListener", 101, VX_FP_TASK, 4096, (FUNCPTR)spawnVisionListener, (int)this,0,0,0,0,0,0,0,0,0);
}



void VisionListener::handle() {
  VisionMessage tmp;
  while ( true ) {
    recvfrom(sock, (char*)&tmp, sizeof(VisionMessage), 0, 0, 0);
    semTake(mutex, WAIT_FOREVER);
    memcpy(&msg, &tmp, sizeof(VisionMessage));
    semGive(mutex);
  }
}


VisionMessage VisionListener::getNewestMessage() {
  VisionMessage tmp;
  semTake(mutex, WAIT_FOREVER);
  memcpy(&tmp, &msg, sizeof(VisionMessage));
  semGive(mutex);
  return tmp;
}
