#include "main.h"

void operatorControl() {
	while (1) {
		driveOp();
		intakeOp();
		descoreOp();
		launcherOp();
		adjusterOp();
		delay(20);
	}
}
