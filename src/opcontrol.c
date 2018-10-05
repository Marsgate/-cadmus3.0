#include "main.h"

void operatorControl() {

	operatorLCD();

	while (1) {

		//robot control
		driveOp();
		intakeOp();
		descoreOp();
		launcherOp();
		adjusterOp();

		//feedback
		lcdClear(uart1);
		lcdPrint(uart1, 1, "1: %d, 2:%d", encoderGet(enc_l), encoderGet(enc_r));
		lcdPrint(uart1, 2, "Gyro:%d", gyroGet(gyro));

		delay(20);
	}
}
