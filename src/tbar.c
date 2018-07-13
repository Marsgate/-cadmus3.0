#include "main.h"

void tbar(int vel){
  motorSet(TBAR1, vel);
}

void tbarOp(){
  static int vel;

  tbar(vel);

  if(joystickGetDigital(1, 7, JOY_UP))
    vel = 127;
  else if(joystickGetDigital(1, 7, JOY_DOWN))
    vel = -127;
  else{
    if(vel > 0)
      tbar(vel/6);
    else
      vel = 0;
  }
}
