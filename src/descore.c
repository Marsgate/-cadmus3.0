#include "main.h"

void descore(int vel){
  motorSet(DESCORE, vel);
}

void descoreOp(){
  static int vel;

  descore(vel);

  if(buttonGetState(JOY1_8U))
    vel = 127;
  else if(buttonGetState(JOY1_8D))
    vel = -127;
  else
    vel = 0;

}
