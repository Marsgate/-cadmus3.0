#include "main.h"

TaskHandle intakeHandle;

void intake(int vel){
  motorSet(INTAKE, vel);
}

bool hasBall(){
  if(analogRead(LINE_L) < 2000 || analogRead(LINE_R) < 2000)
    return true;
  else
    return false;
}

void intakeOp(){
  static int vel;

  intake(vel);

  if(buttonGetState(JOY1_6U))
    vel = 127;
  else if(buttonGetState(JOY1_5U))
    vel = -127;
  else
    vel = 0;
}


//task
void intakeBallTask(void * parameter){
  intake(127);
  while(!hasBall()) delay(20);
  intake(0);
  taskDelete(intakeHandle); // stop running the task
}

void intakeBall(){
  intakeHandle = taskCreate(intakeBallTask, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}
