#include "main.h"

#define TL *644

void highFlag(){
  //launch the ball
  launcher(127);
  while(!isFired()) delay(20);
  launcher(0);

  //drive to the nearest cap
  autoTurn(-90);
  while(isDriving()) delay(20);
  autoDrive(2 TL);
  while(isDriving()) delay(20);

  //intake while reversing
  intake(127);
  autoDrive(-.5 TL);
  while(!hasBall() && isDriving()) delay(20);

  //park
  autoTurn(90);
  while(isDriving()) delay(20);
  intake(0);
  autoDrive(1.5 TL);
  while(isDriving()) delay(20);
}

void midFlag(){

}

void skills(){
  //flip the nearest cap
  autoDrive(2.2 TL);
  intake(-40);
  while(encoderGet(enc_r) < 1.9 TL) delay(20);
  intake(127);
  while(!hasBall()) delay(20);
  intake(0);
  while(isDriving()) delay(20);


  //back up against wall
  autoDrive(-2.2 TL);
  intake(0);
  while(isDriving()) delay(20);

  //align with flags
  autoTurn(80);
  while(isDriving()) delay(20);

  //launch the balls
  launcher(127);
  while(!isFired()) delay(20);
  intake(127);
  adjuster(127);
  delay(400);
  launcher(0);
  delay(600);
  adjuster(10);
  launcher(127);
  while (!isFired()) delay(20);
  launcher(0);
  intake(0);

  //toggle the low flag
  autoTurn(14);
  while(isDriving()) delay(20);
  autoDrive(2.5 TL);
  while(isDriving()) delay(20);

  //backup to align with next cap
  autoDrive(-1.1 TL);
  while(isDriving()) delay(20);

  //line up with the wall
  autoTurn(-90);
  while(isDriving()) delay(20);
  autoDrive(-.4 TL);
  while(isDriving()) delay(20);


  //flip next cap
  intake(-80);
  autoDrive(1.5 TL);
  while(isDriving()) delay(20);
  autoDrive(-.5);
  while(isDriving()) delay(20);
  intake(0);

  //align for park
  autoTurn(-75);
  while(isDriving()) delay(20);
  autoDrive(1.5 TL);
  while(isDriving()) delay(20);

  //alliance park
  autoDrive(2 TL);
  while(encoderGet(enc_r) < .9 TL) delay(20);
  autoDrive(-1);
  while(isDriving()) delay(20);

  //align for park
  autoTurn(85);
  while(isDriving()) delay(20);
  autoDrive(.5 TL);
  while(isDriving()) delay(20);

  //center park
  autoDrive(2 TL);
  while(encoderGet(enc_r) < .9 TL) delay(20);
  autoDrive(-1);
  while(isDriving()) delay(20);
}

void autonomous() {

  TaskHandle driveHandle = taskRunLoop(drivePID, 20); //start claw
  TaskHandle turnHandle = taskRunLoop(turnPID, 20); //start claw

  switch(auton){
    case 0:
      skills();
      break;
    case 1:
      break; //None
    case 2:
      highFlag();
      break;
    case 3:
      midFlag();
  }

  //stop all tasks
  taskDelete(driveHandle);
  taskDelete(turnHandle);
  motorStopAll();
}
