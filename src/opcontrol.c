#include "main.h"

void control(){
  tankOp();
  intakeOp();
  descoreOp();
  launcherOp();
  adjusterOp();
}

void operatorControl() {

  operatorLCD();

  while (1) {

    control();

    //feedback
    lcdClear(uart1);
    lcdPrint(uart1, 1, "L: %d, R:%d", encoderGet(enc_l), encoderGet(enc_r));
    lcdPrint(uart1, 2, "Gyro: %d", gyRead());
    delay(20);
  }
}
