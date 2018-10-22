#include "main.h"

void control(){
  arcadeOp();
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
    //lcdPrint(uart1, 2, "Gyro:%d", gyroGet(gyro));
    /*
    lcdPrint(uart1, 1, "L:%d C:%d R:%d",
      analogRead(LINE_L)/100,
      analogRead(LINE_C)/100,
      analogRead(LINE_R)/100
    );
    lcdPrint(uart1, 2, "hasBall: %d", hasBall());
    */
    //lcdPrint(uart1, 2, "isDriving: %d", isDriving());

    delay(20);
  }
}
