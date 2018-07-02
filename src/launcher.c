#include "main.h"

void launcher(int vel){
  motorSet(LAUNCHER1, vel);
  motorSet(LAUNCHER2, vel);
}

void launcherOp(){
  if(buttonGetState(JOY1_8R))
    launcher(127);
  else
    launcher(0);
}
