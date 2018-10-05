#include "main.h"

void highFlag(){
  autoDrive(1000);
  while(1) delay(20);
}

void midFlag(){

}

void skills(){

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
