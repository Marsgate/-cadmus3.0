#include "main.h"

#define TL *644

static int park = false;

void close(){
  //launch the ball
  launcher(127);
  while(!isFired()) delay(20);
  launcher(0);

  //toggle the low flag
  autoTurn(13);
  intake(-127);
  autoDrive(2.5 TL);
  intake(0);

  //backup to align with next cap
  autoDrive(-1.1 TL);

  //line up with the wall
  autoTurn(-90);
  autoDrive(-.4 TL);

  //flip next cap
  intake(-80);
  autoDrive(1.5 TL);
  intake(0);

  //align with platform
  autoTurn(-83);
  autoDrive(1.3 TL);

  // if auto is not a parking auton, exit
  if(!park)
    return;

  //alliance park
  startDrive(2 TL);
  while(encoderGet(enc_r) < .9 TL) delay(20);
  autoDrive(-1);
}

void far(){
  //launch the ball
  launcher(127);
  while(!isFired()) delay(20);
  launcher(0);

  //align with wall
  autoDrive(-1.3 TL);

  //face cap
  autoDrive(.2 TL);
  autoTurn(-90);

  //flip cap
  intake(-127);
  startDrive(1.2 TL);
  while(encoderGet(enc_r) < .6 TL) delay(20);
  driveSpeed(2 TL, 20);
  while(encoderGet(enc_r) < 1.2 TL) delay(20);


  //face platform
  autoDrive(-.55 TL);
  intake(0);
  autoTurn(85);

  //drive to platform
  autoDrive(1.4 TL);

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
  intake(-127);
  startDrive(2.4 TL);
  while(encoderGet(enc_r) < 2 TL) delay(20);
  intakeBall();
  while(encoderGet(enc_r) < 2.1 TL) delay(20);

  //back up against wall
  startDrive(-.4 TL);
  while(encoderGet(enc_r) > -.2 TL) delay(20);
  startDrive(-2.4 TL);

  while(isDriving()) delay(20);

  //align with flags
  autoDrive(.4 TL);
  autoTurn(90);

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
  autoTurn(11);
  intake(-127);
  autoDrive(2.5 TL);
  intake(0);

  //backup to align with next cap
  autoDrive(-1.1 TL);

  //line up with the wall
  autoTurn(-90);
  autoDrive(-.4 TL);

  //flip next cap
  intake(-80);
  autoDrive(1.5 TL);
  intake(0);

  //align against wall
  autoDrive(-1.7 TL);
  autoDrive(.4 TL);

  //align for park
  autoTurn(-90);
  autoDrive(2 TL);
  autoTurn(90);
  autoDrive(.7 TL);

  //alliance park
  startDrive(2 TL);
  while(encoderGet(enc_r) < .9 TL) delay(20);
  autoDrive(-1);

  //center park
  autoDrive(.3 TL);
  startDrive(2 TL);
  while(encoderGet(enc_r) < .9 TL) delay(20);
  autoDrive(-1);



  /* old park
  //align for park
  autoTurn(-75);
  autoDrive(1.5 TL);

  //alliance park
  startDrive(2 TL);
  while(encoderGet(enc_r) < .9 TL) delay(20);
  autoDrive(-1);

  //align for park
  autoTurn(85);
  autoDrive(.5 TL);

  //center park
  startDrive(2 TL);
  while(encoderGet(enc_r) < .9 TL) delay(20);
  autoDrive(-1);
  */
}

void autonomous() {

  TaskHandle driveHandle = taskRunLoop(driveControl, 20);
  TaskHandle turnHandle = taskRunLoop(turnControl, 20);

  switch(auton){
    case 0:
      skills();
      break;
    case 1:
      autoTurn(90);
      autoTurn(-90);
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
