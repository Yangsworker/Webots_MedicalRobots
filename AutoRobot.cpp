
#include <webots/Robot.hpp>
#include <webots/Motor.hpp>
#include <webots/PositionSensor.hpp>
#include <webots/InertialUnit.hpp>
#include <user.h>
#include <time.h>
#include <webots/utils/AnsiCodes.hpp>
#include <Device/inc/dbus.h>
#include "USER_Task/inc/chassis_task.h"
int timeStep = 0;
using namespace webots;
using namespace std;
int loopCnt = 0;
double titaClock = 0;

/**
 * @note 一切传感器初始化均需要在timeStep获取之后进行
 *       一切webots函数的执行均需要在robot构建之后进行
 */
int main(int argc, char **argv)
{
	Robot *robot = new Robot();
	timeStep = (int)robot->getBasicTimeStep();
    Chassis chassis;
	while (robot->step(timeStep) != -1)
	{
		if (loopCnt % 1 == 0) // 500Hz
		{
			chassis.chassis_run();	
		}
		if (loopCnt % 5 == 0) // 100Hz
		{
			chassis.state->getSensorValue_100hz();   //获取图像处理消息
		}
		if (loopCnt % 10 == 0) // 50Hz
		{
		}
		if (loopCnt % 50 == 0) // 10Hz
		{
		}
		if (loopCnt % 500 == 0) // 1Hz
		{
			loopCnt = 0;
		}
		loopCnt++;
		titaClock = titaClock + 0.002;
	};

	delete robot;
	return 0;
}
