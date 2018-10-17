#include "main.h"

void adjuster(int vel){
  motorSet(ADJUSTER, vel);
}

void adjusterOp(){
  static int vel = 0;
  static int d = 0;
  static int t = 0;
  t++;

  //first run initializer of d
  if(d == 0){
    if(digitalRead(5))
      d = 1;
    else
      d = -1;
  }

  adjuster(vel);

  if(buttonIsNewPress(JOY1_5D))
    vel = 127*d, t = 0, d = -d;
  else if(t > 45)
      adjuster(vel/12.7);
}
