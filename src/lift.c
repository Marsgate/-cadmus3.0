#include "main.h"

void lift(int vel){
  motorSet(LIFT1, vel);
}

void liftOp(){
  static int vel;

  lift(vel);

  if(joystickGetDigital(1, 5, JOY_UP))
    vel = 127;
  else if(joystickGetDigital(1, 5, JOY_DOWN))
    vel = -127;
  else{
    if(vel > 0)
      lift(vel/6);
    else
      vel = 0;
  }
}
