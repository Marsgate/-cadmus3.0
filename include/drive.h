#ifndef DRIVE_H_
#define DRIVE_H_

void drive(int vel);

void driveOp();

void autoDrive(int sp);
void autoTurn(int sp);

void drivePID();
void turnPID();

bool isDriving();

#endif
