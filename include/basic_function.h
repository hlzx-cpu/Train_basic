#ifndef BASIC_FUNCTIONS_H_
#define BASIC_FUNCTIONS_H_
#include "robot_config.h"

void moveIntake(float pct);
void moveShooter(float pct);

void setMotorEvent(int _event);
void autonMotor();

double rawIMUHeading();
double IMUHeading();
void resetIMU();

double getDis();
void moveForwardVoltage(int voltage);
void turnRightVoltage(int voltage);
void brakeChassic();
void resetMotor();


void moveTo(double targetDis, int timeout = 1000, double maxPercentage = 80, int tol_dis,
            int tol_time, double _kp, double _ki, double _kd, double _i_range,
            double _i_max);
void turnTo(double targetAngle, int timeout = 1000, double maxPercentage = 80, int tol_angle,
            int tol_time, double _kp, double _ki, double _kd, double _i_range,
            double _i_max);

#endif