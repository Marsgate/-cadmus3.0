#include "main.h"
#include <math.h>

static bool driveMode = true;
static int driveTarget = 0;
static int turnTarget = 0;
static int maxSpeed = 127;

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
//dual gyro control
int gyRead(){
  int gyroVal = (gyroGet(gy1) - gyroGet(gy2))/2;
  return gyroVal;
}

void gyReset(){
  gyroReset(gy1);
  gyroReset(gy2);
}

/**************************************************/
//drive control
void driveControl(){

  static int prevError = 0;

  if(!driveMode)
    return;

  int sp = driveTarget;

  double kp = .2;
  double kd = .5;

  //read sensors
  int ls = encoderGet(enc_l);
  int rs = encoderGet(enc_r);
  int sv = (ls+rs)/2;

  //speed
  int error = sp-sv;
  int derivative = error - prevError;
  prevError = error;
  int speed = error*kp + derivative*kd;

  if(speed > maxSpeed)
    speed = maxSpeed;
  if(speed < -maxSpeed)
    speed = -maxSpeed;

  //set motors
  left(speed);
  right(speed);
}

void turnControl(){

  if(driveMode)
    return;

  static int prevError;

  int sp = turnTarget;

  if(mirror == true)
    sp = -sp; // inverted turn speed for blue auton

  //int ab = abs(sp); //absolute setpoint
  double kp = 1.3;
  double kd = 6;

  int sv = gyRead();
  int error = sp-sv;
  int derivative = error - prevError;
  prevError = error;
  int speed = error*kp + derivative*kd;

  turn(speed);

  printf("Error %d\n", error);
}


/**************************************************/
//autonomous functions
void startDrive(int sp){
  maxSpeed = 127;
  encoderReset(enc_l);
  encoderReset(enc_r);
  driveTarget = sp;
  driveMode = true;
}

void startTurn(int sp){
  gyroReset(gy1);
  gyroReset(gy2);
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

void driveSpeed(int sp, int speed){
  startDrive(sp);
  maxSpeed = speed;
}

bool isDriving(){
  static int count = 26;
  static int last = 0;
  static int lastTarget = 0;



  int curr = encoderGet(enc_r);
  int thresh = 2;
  int target = turnTarget;

  if(driveMode)
    target = driveTarget;


  if(abs(last-curr) < thresh)
    count++;
  else
    count = 0;


  if(target != lastTarget)
    count = 0;

  lastTarget = target;
  last = curr;

  //not driving if we haven't moved in .5
  if(count > 25)
    return false;
  else
    return true;

}


/**************************************************/
//operator control
void tankOp(){
  int lJoy = joystickGetAnalog(1, 3);
  int rJoy = joystickGetAnalog(1, 2);
  left(lJoy >= 0 ? trueSpeed[abs(lJoy)] : -trueSpeed[abs(lJoy)]);
  right(rJoy >= 0 ? trueSpeed[abs(rJoy)] : -trueSpeed[abs(rJoy)]);
}


void arcadeOp(){
  int vJoy = joystickGetAnalog(1, 2);
  int hJoy = joystickGetAnalog(1, 4);

  //true speed
  int v = vJoy >= 0 ? trueSpeed[abs(vJoy)] : -trueSpeed[abs(vJoy)];
  int h = hJoy >= 0 ? trueSpeed[abs(hJoy)] : -trueSpeed[abs(hJoy)];

  //speed calculation
  int l = v+h;
  int r = v-h;

  //scaling for over power
  if(abs(l) > 127)
    r *= (127/l);
  if(abs(r) > 127)
    l *= (127/r);

  left(l);
  right(r);
}
