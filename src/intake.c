#include "main.h"

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
