#ifndef DRIVE_H_
#define DRIVE_H_

void drive(int vel);

void driveOp();

void startDrive(int sp);
void startTurn(int sp);
void autoDrive(int sp);
void autoTurn(int sp);

void driveControl();
void turnControl();

bool isDriving();

#endif
