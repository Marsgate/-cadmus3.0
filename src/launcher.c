#include "main.h"

void launcher(int vel){
  motorSet(LAUNCHER1, vel);
  motorSet(LAUNCHER2, vel);
}

void launcherOp(){
  if(joystickGetDigital(1, 8, JOY_RIGHT))
    launcher(127);
  else
    launcher(0);
}
