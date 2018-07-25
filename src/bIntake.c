#include "main.h"

void bIntake(int vel){
  motorSet(B_INTAKE1, vel);
}

void bIntakeOp(){
  static int vel;

  bIntake(vel);

  if(joystickGetDigital(1, 6, JOY_UP))
    vel = 127;
  else if(joystickGetDigital(1, 8, JOY_UP))
    vel = -127;
  else{
    if (vel > 0)
      vel = 0;
  }
}
