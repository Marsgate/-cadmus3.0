#include "main.h"

void descore(int vel){
  motorSet(DESCORE, vel);
}

void descoreOp(){
  static int vel;

  descore(vel);

  if(buttonGetState(JOY1_7U))
    vel = 127;
  else if(buttonGetState(JOY1_7D))
    vel = -127;
  else
    vel = 0;

}
