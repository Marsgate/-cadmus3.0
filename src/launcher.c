#include "main.h"

TaskHandle launcherHandle;

void launcher(int vel){
  motorSet(LAUNCHER, vel);
}

bool isFired(){
  if(analogRead(LINE_C) < 2000)
    return true;
  else
    return false;
}

void launcherOp(){
  static int vel = 0;
  static int t = 0;

  launcher(vel);

  if(buttonGetState(JOY1_6D))
    vel = 127;
  else
    vel = 0;


  static int panic = false;
  if(buttonIsNewPress(JOY1_7U))
    panic = !panic;


  //auto ratcheting
  if(isFired() && !panic)
    t = 20;
  if(t > 0)
    vel = 127;
  t--;

}

//tasks
void autoShootTask(void * parameter){
  launcher(127);
  while(!isFired()) delay(20);
  delay(500);
  launcher(0);
  taskDelete(launcherHandle); // stop running the task
}

void autoShoot(){
  launcherHandle = taskCreate(autoShootTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}
