#include "main.h"

void lift(int vel){
  motorSet(LIFT1, vel);
  motorSet(LIFT2, vel);
}

void liftOp(){
  if(joystickGetDigital(1, 5, JOY_UP))
    lift(127);
  else if(joystickGetDigital(1, 5, JOY_DOWN))
    lift(-127);
  else
    lift(0);
}
