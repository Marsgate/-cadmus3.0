#include "main.h"

#define AUTO_COUNT 7


void portTest(){
  int i = 1;

  while(1){
    lcdPrint(uart1, 1, "Port: %d", i);
    motorStopAll();

    if(buttonGetState(LCD_CENT))
      motorSet(i, 127);

    if(buttonIsNewPress(LCD_RIGHT))
      i++;

    if(buttonIsNewPress(LCD_LEFT))
      i--;

    delay(20);
  }
}


void operatorLCD(){
  // only run debug in non competition
  lcdClear(uart1);

  while(isOnline() == false){
    float p1 = powerLevelMain();
    lcdPrint(uart1, 2, "Battery:%0.2f", p1/1000);
    lcdSetText(uart1, 1, "Op ------- Debug");

    if(buttonIsNewPress(LCD_LEFT))
      break;
    if(buttonIsNewPress(LCD_RIGHT))
      portTest();
    if(buttonGetState(JOY1_7L))
      autonomous();

    delay(20);
  }
}


void initializationLCD(){

  const char *autoNames[AUTO_COUNT] = {"Skills", "None", "Close Park", "Far Park", "Close No Park", "Far No Park", "bigBoi"};
  auton = 1; // start with none as default
  int selected = 0; //layered selection

  while(selected < 2){
    lcdSetText(uart1, 2, "");

    while(selected < 1){
      if(buttonIsNewPress(LCD_CENT)){
        selected++;
      }else if(buttonIsNewPress(LCD_LEFT)){
        if(auton > 0) auton--;
      }else if(buttonIsNewPress(LCD_RIGHT)){
        if(auton < AUTO_COUNT-1) auton++;
      }

      lcdSetText(uart1, 1, autoNames[auton]);
      delay(20);
    }

    lcdSetText(uart1, 2, "red ----- blue");
    if(buttonIsNewPress(LCD_CENT)){
      selected--;
    }else if(buttonIsNewPress(LCD_LEFT)){
      selected++;
      lcdSetText(uart1, 2,"red selected");
    }else if(buttonIsNewPress(LCD_RIGHT)){
      selected++;
      lcdSetText(uart1, 2,"blue selected");
      mirror = true;
    }
    delay(20);
  }
}
