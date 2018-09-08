#include "main.h"

void launcher(int vel){
  motorSet(LAUNCHER1, vel);
}

void launcherOp(){
  static int vel;

  launcher(vel);

  if(buttonGetState(JOY1_6D) || digitalRead(L_LIMIT))
    vel = 127; //
  else{
    vel = 0;
  }

  if(buttonGetState(JOY1_7U) && digitalRead(L_LIMIT)){
    vel = 0;
  }

}
