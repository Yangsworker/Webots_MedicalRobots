#pragma once
#include <user.h>
#include <webots/Motor.hpp>
#include <Device/inc/positionSense.h>

#include <time.h>
using namespace webots;

class MotorCtrl
{
public:
	MotorCtrl(string MotorName, string SensorName);
	void motorInit();
	Motor* motor;
	positionSense* motorSensor;
	string motorName, sensorName;
	double speedTime, speedTime_last;
	double accTime, accTime_last;
	double motorFbPosition;
	double motorFbPosition_last;
	double motorFbPosition_total;
	int motorFbPosition_cnt;
	double motorFbSpeed;
	double motorFbSpeed_last;
	double motorFbAcc;
	double motorSetPosition;
	double motorSetSpeed;
	double motorSetTorque;
	double maxTorque;
	int8_t ctrlPossitive;
	float getMotorFbSpeed();
	float getMotorFbPosition();
	float getMotorFbAccelerate();
	void setMotorTorque(double torque);
	void setMotorSpeed(double speed);
	void setMotorPosition(double position);
	double getMotorTorque(void);
	void setMotorMaxTorque(double maxT);
	void setMotorPossitive(int8_t _p);
	void feedbackPossitive(int8_t _p);
	void printMotorInfo(string message);
};
