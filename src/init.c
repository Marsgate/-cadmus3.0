
#include "main.h"
#include "lcd.h"

void initializeIO() {

}

void initialize() {
  setTeamName("574C Centurion");
  buttonInit();

  //sensor initialization
  enc_l = encoderInit(ENC_L1, ENC_L2, false);
  enc_r = encoderInit(ENC_R1, ENC_R2, false);
  gyro = gyroInit(GYRO, 0);

  //lcd
  lcdInit(uart1);
  lcdClear(uart1);
  lcdSetBacklight(uart1, true);
  initializationLCD();
}
