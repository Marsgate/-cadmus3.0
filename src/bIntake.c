#include "main.h"

void bIntake(int vel){
  motorSet(B_INTAKE1, vel);
}

void bIntakeOp(){
  static int vel;

  bIntake(vel);

  if(buttonGetState(JOY1_6U))
    vel = 127;
  else if(buttonGetState(JOY1_8D))
    vel = -127;
  else{
    if (vel > 0)
      vel = 0;
  }
}
