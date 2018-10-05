#include "main.h"

void launcher(int vel){
  motorSet(LAUNCHER, vel);
}

bool isFired(){
  if(analogRead(LINE_C) < 2000)
    return true;
  else
    return false;
}

void launcherOp(){
  static int vel = 0;
  static int t = 0;

  launcher(vel);

  if(buttonGetState(JOY1_6D))
    vel = 127;
  else
    vel = 0;


  //auto ratcheting
  if(isFired())
    t = 25;
  if(t > 0)
    vel = 127;
  t--;

}
