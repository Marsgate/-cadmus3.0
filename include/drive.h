#ifndef DRIVE_H_
#define DRIVE_H_

void driveOp();

void autoDrive(int sp);
void autoTurn(int sp);

void drivePID();
void turnPID();

bool isDriving();
bool isTurning();

#endif
