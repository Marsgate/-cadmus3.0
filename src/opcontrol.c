#include "main.h"

void operatorControl() {
	while (1) {
		driveOp();
		liftOp();
		launcherOp();
		tbarOp();
		clawOp();
		delay(20);
	}
}
