#include "main.h"

void lift(int vel){
  motorSet(LIFT1, vel);
  motorSet(LIFT2, vel);
}

void liftOp(){
  static int vel;

  lift(vel);

  if(buttonGetState(JOY1_5U))
    vel = 127;
  else if(buttonGetState(JOY1_5D))
    vel = -127;
  else{
      vel = 0;
  }
}
