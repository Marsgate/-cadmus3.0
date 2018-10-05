#include "main.h"

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
//autonomous control
void autoDrive(int sp){
  double kp = .13;

  //int sv = (encoderGet(enc_l)+encoderGet(enc_r))/2;
	int sv = encoderGet(enc_r);
  int error = sp-sv;
  int speed = error*kp;

  drive(speed);
}

void autoTurn(int sp){
	if(mirror == true)
    sp = -sp; // inverted turn speed for blue auton

  double kp = .75;

	int sv = gyroGet(gyro);
  int error = sp-sv;
  int speed = error*kp;

  turn(speed);
}

bool isDriving(){
	static int count = 0;
	static int last = 0;
	int curr = encoderGet(enc_r);

	if(abs(last-curr) < 5)
		count++;
	else{
		count = 0;
	}

	last = curr;

	if(count > 25){
		return false;
	}else
		return true;

}

bool isTurning(){
	static int count = 0;
	static int last = 0;
	int curr = gyroGet(gyro);

	if(abs(last-curr) < 1)
		count++;
	else{
		count = 0;
	}

	last = curr;

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
