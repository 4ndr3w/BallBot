#include "Subsystem.h"
#include "taskLib.h"

void subsystemTask(void* subsystem)
{
  while ( true ) {
    lock();
    ((Subsystem*)subsystem)->update();
    unlock();
    Wait(0.05);
  }
}

Subsystem::Subsystem() : taskId(-1) {
  mutex = semMCreate(SEM_Q_FIFO);
}

void Subsystem::startUpdateTask(char* description)
{
  if ( taskId == -1 ) {
    taskId = taskSpawn(description, 101, VX_FP_TASK, 4096, (FUNCPTR)spawnTCPServerHandler, (int)this,0,0,0,0,0,0,0,0,0);
  }
  else
    printf("startUpdateTask called on \"%s\" when task was already running (as %i)", description, taskId);
}

void Subsystem::lock() {
  semTake(mutex, WAIT_FOREVER);
}

void Subsystem::unlock() {
  semGive(mutex);
}
