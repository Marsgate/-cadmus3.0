#include "main.h"

#define TL *644

static int park = false;

void close(){
  //launch the ball
  autoShoot();
  while(!isFired()) delay(20);
  intake(0);

  //toggle the low flag
  if(mirror)
    autoTurn(10);
  else
    autoTurn(13);
  loadBall();
  autoDrive(2.5 TL);

  //backup to align with next cap
  autoDrive(-1.1 TL);

  //line up with the wall
  autoTurn(-90);
  autoDrive(-.4 TL);

  //flip next cap
  intake(-80);
  startDrive(1.5 TL);
  while(encoderGet(enc_r) < .8 TL) delay(20);
  setSpeed(20);
  while(isDriving()) delay(20);
  intake(0);

  // if auto is not a parking auton, exit
  if(!park)
    return;

  //align with platform
  if(mirror)
    autoTurn(-83);
  else
    autoTurn(-73);
  autoDrive(1.5 TL);

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
  autoDrive(.25 TL);
  autoTurn(-90);

  //align against the wall
  autoDrive(-.5 TL);

  //flip cap
  intake(-127);
  startDrive(3.4 TL);
  while(encoderGet(enc_r) < .9 TL) delay(20);
  setSpeed(20);
  while(encoderGet(enc_r) < 2.1 TL) delay(20);
  intake(0);
  while(encoderGet(enc_r) < 2.3 TL) delay(20);

  //face platform
  autoDrive(-.6 TL);
  intake(0);
  autoTurn(84);

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

void bigBoi(){
  //flip the nearest cap
  intake(127);
  startDrive(3 TL);
  while(encoderGet(enc_r) < 1.5 TL) delay(20);
  setSpeed(20);
  intakeBall();
  while(encoderGet(enc_r) < 1.9 TL) delay(20);

  //back up against wall
  startDrive(-2.2 TL);
  setSpeed(80);
  while(encoderGet(enc_r) > -.2 TL) delay(20);
  setSpeed(127);
  while(isDriving()) delay(20);

  //align with flags
  autoDrive(.35 TL);
  autoTurn(90);

  //launch the balls
  autoShoot();
  while(!isFired()) delay(20);
  intake(127);
  adjuster(127);
  delay(1000);
  adjuster(10);

  close();

  //align with flags in the center
  adjuster(-127);
  if(mirror)
    autoTurn(45);
  else
    autoTurn(50);
  autoShoot();
  adjuster(-10);
  startDrive(1.8 TL);
  setSlant(70);
  while(isDriving()) delay(20);
}

void skills(){
  //flip the nearest cap
  intake(-127);
  startDrive(3 TL);
  while(encoderGet(enc_r) < 1.5 TL) delay(20);
  setSpeed(20);
  while(encoderGet(enc_r) < 1.9 TL) delay(20);
  intakeBall();
  while(encoderGet(enc_r) < 2.5 TL) delay(20);

  //back up against wall
  startDrive(-2.4 TL);
  setSpeed(80);
  while(encoderGet(enc_r) > -.2 TL) delay(20);
  setSpeed(127);
  while(isDriving()) delay(20);

  //align with flags
  autoDrive(.4 TL);
  autoTurn(90);

  //launch the balls
  autoShoot();
  while(!isFired()) delay(20);
  intake(127);
  adjuster(127);
  delay(1000);
  adjuster(10);

  close();

  //align against wall
  autoDrive(-1.6 TL);
  autoDrive(.4 TL);

  //align for park
  autoTurn(-90);
  autoDrive(1.95 TL);
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
}

void autonomous() {

  TaskHandle driveHandle = taskRunLoop(driveControl, 20);
  TaskHandle turnHandle = taskRunLoop(turnControl, 20);

  gyReset();
  encoderReset(enc_r);
  encoderReset(enc_l);


  switch(auton){
    case 0:
      skills();
      break;
    case 1:
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
      break;
    case 6:
      bigBoi();
      break;
  }

  //stop all tasks
  taskDelete(driveHandle);
  taskDelete(turnHandle);
  motorStopAll();
}
