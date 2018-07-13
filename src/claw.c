#include "main.h"

void claw(int vel){
  motorSet(CLAW1, vel);
}

void clawOp(){
  static int vel;

  claw(vel);

  if(joystickGetDigital(1, 6, JOY_UP))
    vel = 127;
  else if(joystickGetDigital(1, 6, JOY_DOWN))
    vel = -127;
  else{
    if(vel > 0)
      claw(vel/6);
    else
      vel = 0;
  }
}
