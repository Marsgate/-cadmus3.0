#include "main.h"

#define TL *644

static int park = false;

void close(){

}

void far(){
  //launch the ball
  launcher(127);
  while(!isFired()) delay(20);
  launcher(0);

  //turn to the cap
  autoTurn(-90);

  //intake the ball cap
  autoDrive(2.2 TL);
  intake(127);
  while(!hasBall()) delay(20);
  intake(0);

  //turn to second cap
  autoTurn(-90);

  //flip second cap
  intake(-127);
  autoDrive(1 TL);
  autoDrive(-.3);
  intake(0);

  //align with park
  autoTurn(-160);
  autoDrive(1.2 TL);


  // if auto is not a parking auton, exit
  if(!park)
    return;

  //alliance park
  startDrive(2 TL);
  while(encoderGet(enc_r) < .9 TL) delay(20);
  autoDrive(-1);
}

void skills(){
  //flip the nearest cap
  intake(-40);
  startDrive(2.2 TL);
  while(encoderGet(enc_r) < 1.9 TL) delay(20);
  intake(127);
  while(!hasBall()) delay(20);
  intake(0);
  while(isDriving()) delay(20);


  //back up against wall
  intake(0);
  autoDrive(-2.2 TL);

  //align with flags
  autoTurn(80);

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
  autoDrive(2.5 TL);

  //backup to align with next cap
  autoDrive(-1.1 TL);

  //line up with the wall
  autoTurn(-90);
  autoDrive(-.4 TL);


  //flip next cap
  intake(-80);
  autoDrive(1.5 TL);
  autoDrive(-.5);
  intake(0);

  //align for park
  autoTurn(-75);
  autoDrive(1.5 TL);

  //alliance park
  startDrive(2 TL);
  while(encoderGet(enc_r) < .9 TL) delay(20);
  autoDrive(-1);
  while(isDriving()) delay(20);

  //align for park
  autoTurn(85);
  autoDrive(.5 TL);

  //center park
  startDrive(2 TL);
  while(encoderGet(enc_r) < .9 TL) delay(20);
  autoDrive(-1);
}

void autonomous() {

  TaskHandle driveHandle = taskRunLoop(driveControl, 20);
  TaskHandle turnHandle = taskRunLoop(turnControl, 20);

  switch(auton){
    case 0:
      skills();
      break;
    case 1:
      autoDrive(3000);
      break; //None
    case 2:
      park = true;
      close();
      break;
    case 3:
      park = true;
      far();
      break;
    case 4:
      close();
      break;
    case 5:
      far();
  }

  //stop all tasks
  taskDelete(driveHandle);
  taskDelete(turnHandle);
  motorStopAll();
}
