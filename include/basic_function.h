#ifndef BASIC_FUNCTIONS_H_
#define BASIC_FUNCTIONS_H_
#include "robot_config.h"

void setMotorEvent(int _event);
void autonMotor();
void IMUReset();

void turnTo(double tar_angle);
void moveTo(double target);

void moveIntake(float pct);
void moveShooter(float pct);

void autonMotor();

#endif