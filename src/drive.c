#include "main.h"

static bool driveMode = true;
static int driveTarget = 0;
static int turnTarget = 0;

/**************************************************/
//true speed array
const int trueSpeed[128] = {
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  13, 14, 14, 14, 14, 14, 15, 15, 15, 15,
  16, 16, 16, 16, 16, 16, 17, 17, 17, 17,
  18, 18, 18, 18, 18, 19, 19, 19, 20, 20,
  20, 20, 21, 21, 21, 22, 22, 22, 22, 23,
  23, 23, 24, 24, 24, 24, 25, 25, 25, 26,
  26, 26, 27, 27, 27, 28, 28, 28, 29, 29,
  30, 30, 31, 31, 32, 32, 33, 33, 34, 35,
  35, 36, 37, 37, 38, 39, 39, 40, 41, 41,
  42, 43, 44, 45, 46, 46, 47, 48, 49, 50,
  51, 53, 54, 55, 57, 60, 62, 65, 69, 72,
  76, 80, 82, 85, 87, 91, 101, 127
};


/**************************************************/
//basic drive functions
void left(int vel){
  motorSet(LDRIVE1, vel);
  motorSet(LDRIVE2, vel);
}

void right(int vel){
  motorSet(RDRIVE1, vel);
  motorSet(RDRIVE2, vel);
}

void drive(int vel){
  left(vel);
  right(vel);
}

void turn(int vel){
  right(vel);
  left(-vel);
}

/**************************************************/
//drive control
void driveControl(){

  if(!driveMode)
    return;

  int sp = driveTarget;

  double kp = 0.16;
  double kp2 = 7;

  //read sensors
  int ls = encoderGet(enc_l);
  int rs = encoderGet(enc_r);
  int sv = (ls+rs)/2;
  int sd = ls-rs;

  //speed
  int error = sp-sv;
  int speed = error*kp;
  int dif = sd*kp2;

  //limiting
  if(speed > 127)
    speed = 127;
  if(speed < -127)
    speed = -127;


  if(abs(error) < 200)
    dif = 0;


  //set motors
  left(speed-dif);
  right(speed+dif);

  printf("speed: %d, ", speed);
  printf("dif: %d\n", dif);
}

void turnControl(){

  if(driveMode)
    return;

  static int prevError;
  int sp = turnTarget;
  if(mirror == true)
    sp = -sp; // inverted turn speed for blue auton

  double kp = 1.5;
  double kd = 4.6;

  int sv = gyroGet(gyro);
  int error = sp-sv;
  int derivative = error - prevError;
  prevError = error;
  int speed = error*kp + derivative*kd;

  turn(speed);

}


/**************************************************/
//autonomous functions
void startDrive(int sp){
  encoderReset(enc_l);
  encoderReset(enc_r);
  driveTarget = sp;
  driveMode = true;
}

void startTurn(int sp){
  gyroReset(gyro);
  turnTarget = sp;
  driveMode = false;
}

void autoDrive(int sp){
  startDrive(sp);
  while(isDriving()) delay(20);
}

void autoTurn(int sp){
  startTurn(sp);
  while(isDriving()) delay(20);
}

bool isDriving(){
  static int count = 26;
  static int last = 0;
  static int lastTarget = 0;

  int curr;
  int thresh;
  int target;

  if(driveMode){
    curr = encoderGet(enc_r);
    thresh = 5;
    target = driveTarget;
  }else{
    curr = gyroGet(gyro);
    thresh = 1;
    target = turnTarget;
  }

  if(abs(last-curr) < thresh)
    count++;
  else{
    count = 0;
  }

  if(target != lastTarget)
    count = 0;

  lastTarget = target;
  last = curr;

  //not driving if we haven't moved in .5
  if(count > 25){
    return false;
  }else
    return true;

}


/**************************************************/
//operator control
void driveOp(){
  int lJoy = joystickGetAnalog(1, 3);
  int rJoy = joystickGetAnalog(1, 2);
  left(lJoy >= 0 ? trueSpeed[abs(lJoy)] : -trueSpeed[abs(lJoy)]);
  right(rJoy >= 0 ? trueSpeed[abs(rJoy)] : -trueSpeed[abs(rJoy)]);
}
