#include "main.h"
#include <math.h>

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

  double kp = .15;
  double kp2 = 2;

  //read sensors
  int ls = encoderGet(enc_l);
  int rs = encoderGet(enc_r);
  int sv = (ls+rs)/2;
  int sd = ls-rs;

  //speed
  int error = sp-sv;
  int speed = error*kp;
  int dif = sd*kp2;

  //speed limiting
  if(speed > 127)
    speed = 127;
  if(speed < -127)
    speed = -127;


  if(speed < 90)
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

  int ab = abs(sp); //absolute setpoint
  double kp = 2.46 * pow(ab, -0.145);
  double kd = (-0.00056 * pow(ab, 2)) + (0.148 * ab) - 2.92;
  if(kd > 5.8)
    kd = 5.8;


  int encoders = ((encoderGet(enc_r)-encoderGet(enc_l))/2)/3.097;
  int gy = gyroGet(gyro);

  int sv = (gy+encoders)/2;
  int error = sp-sv;
  int derivative = error-prevError;
  prevError = error;
  int speed = error*kp + derivative*kd;

  turn(speed);

  printf("kd: %f, ", kd);
  printf("encoders: %d, ", encoders);
  printf("gyro: %d, ", gy);
  printf("Error: %d\n", error);
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
  encoderReset(enc_l);
  encoderReset(enc_r);
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
