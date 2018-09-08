#include "main.h"

void intake(int vel){
  motorSet(INTAKE1, vel);
}

void intakeOp(){
  static int vel;

  intake(vel);

  if(buttonGetState(JOY1_6U))
    vel = 127;
  else if(buttonGetState(JOY1_8U))
    vel = -127;
  else{
    if (vel > 0)
      vel = 0;
  }
}
