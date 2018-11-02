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
void setSpeed(int speed);
void setSlant(int s);

void driveControl();
void turnControl();

bool isDriving();

#endif
