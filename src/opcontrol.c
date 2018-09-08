#include "main.h"

void operatorControl() {
	while (1) {
		driveOp();
		intakeOp();
		descoreOp();
		launcherOp();
		delay(20);
	}
}
