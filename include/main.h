#ifndef MAIN_H_
#define MAIN_H_

#include <API.h>

#ifdef __cplusplus
extern "C" {
#endif

void autonomous();
void initializeIO();
void initialize();
void operatorControl();


//buttons
#include "buttons.h"

//lcd
#include "lcd.h"

//robot system control
#include "drive.h"
#include "intake.h"
#include "descore.h"
#include "launcher.h"
#include "adjuster.h"

//motor ports
#define LDRIVE1 8
#define LDRIVE2 9

#define RDRIVE1 2
#define RDRIVE2 3

#define INTAKE 4

#define DESCORE 6

#define ADJUSTER 7

#define LAUNCHER 10

//digital sensor ports
#define ENC_R1 1
#define ENC_R2 2

#define ENC_L1 3
#define ENC_L2 4


//analog sensor ports
#define GY1 1
#define GY2 5
#define LINE_C 2
#define LINE_L 3
#define LINE_R 4
#define LINE_I 6


//sensors
Encoder enc_l;
Encoder enc_r;
Gyro gy1;
Gyro gy2;


// End C++ export structure
#ifdef __cplusplus
}
#endif

#endif
