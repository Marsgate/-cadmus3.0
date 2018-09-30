#include "main.h"

void intake(int vel){
  motorSet(INTAKE, vel);
}

void intakeOp(){
  static int vel;

  intake(vel);

  if(buttonGetState(JOY1_6U))
    vel = 127;
  else if(buttonGetState(JOY1_5U))
    vel = -65;
  else
    vel = 0;
}
