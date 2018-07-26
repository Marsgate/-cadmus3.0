#include "main.h"

void operatorControl() {
	while (1) {
		driveOp();
		liftOp();
		launcherOp();
		bIntakeOp();
		wristOp();
		delay(20);
	}
}
