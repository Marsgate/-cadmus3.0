#include "main.h"

#define W_TIME 140

void wrist(int vel){
  motorSet(WRIST1, vel);
}

void wristOp(){
  static int vel = 127;
  static int wTime = W_TIME;

  wrist(vel);

  if(buttonIsNewPress(JOY1_6D)){
    vel = -vel;
    wTime = 0;
  }else{
    if(wTime > W_TIME)
      wrist(vel/6);
    wTime += 20;
  }
}
