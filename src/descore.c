#include "main.h"

void descore(int vel){
  motorSet(DESCORE1, vel);
}

void descoreOp(){
  static int vel;

  descore(vel);

  if(buttonGetState(JOY1_5U))
    vel = 127;
  else if(buttonGetState(JOY1_5D))
    vel = -127;
  else{
    vel = 0;
  }
}
