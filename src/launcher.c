#include "main.h"

void launcher(int vel){
  motorSet(LAUNCHER, vel);
}

void launcherOp(){
  static int vel;

  launcher(vel);

  if(buttonGetState(JOY1_6D))
    vel = 127;
  else
    vel = 0;

}
