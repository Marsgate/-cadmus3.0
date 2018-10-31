#ifndef DRIVE_H_
#define DRIVE_H_

void drive(int vel);

void tankOp();
void arcadeOp();

int gyRead();
void gyReset();

void startDrive(int sp);
void startTurn(int sp);
void autoDrive(int sp);
void autoTurn(int sp);
void driveSpeed(int sp, int speed);

void driveControl();
void turnControl();

bool isDriving();

#endif
