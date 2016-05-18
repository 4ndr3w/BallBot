#include "TaskSubsystem.h"
#include "taskLib.h"
#include "stdio.h"
#include "Timer.h"

void subsystemTask(void* subsystem);

TaskSubsystem::TaskSubsystem() : taskId(-1) {
  mutex = semMCreate(SEM_Q_FIFO);
}

void TaskSubsystem::startUpdateTask(char* description)
{
  printf("TaskSubsystem: Starting %s\n", description);
  if ( taskId == -1 ) {
    taskId = taskSpawn(description, 101, VX_FP_TASK, 4096, (FUNCPTR)subsystemTask, (int)this,0,0,0,0,0,0,0,0,0);
  }
  else
    printf("startUpdateTask called on \"%s\" when task was already running (as %i)", description, taskId);
}

void TaskSubsystem::lock() {
  semTake(mutex, WAIT_FOREVER);
}

void TaskSubsystem::unlock() {
  semGive(mutex);
}

void subsystemTask(void* subsystem)
{
  TaskSubsystem* ptr = (TaskSubsystem*)subsystem;
  while ( true ) {
    ptr->lock();
    ptr->update();
    ptr->unlock();
    Wait(0.05);
  }
}
