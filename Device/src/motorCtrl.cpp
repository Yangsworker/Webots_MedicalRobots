#include <Device/inc/motorCtrl.h>
#include <Device/inc/dbus.h>
#define RADIAN 200
#define RAD_TO 57.295779513
MotorCtrl::MotorCtrl(string MotorName, string SensorName)
{
	motor = NULL;
	motorSensor = NULL;
	motorName = MotorName;
	sensorName = SensorName;
	motorFbPosition = 0;
	motorFbPosition_last = 0;
	motorFbSpeed = 0;
	motorFbSpeed_last = 0;
	motorFbAcc = 0;
	motorSetPosition = 0;
	motorSetSpeed = 0;
	motorSetTorque = 0;
	ctrlPossitive = 1;   //默认上力
}


void MotorCtrl::motorInit()
{
	motor = new Motor(motorName);
	motorSensor = new positionSense(sensorName);
	motorSensor->SensorInit(); //初始化传感器
	motor->enableTorqueFeedback(timeStep);   //打开力矩反馈
	ctrlPossitive = 1;
}
/**
 * @brief 设定电机力矩
 */
void MotorCtrl::setMotorTorque(double torque)
{
	if (torque < -maxTorque)
	{
		motorSetTorque = -maxTorque;
	}
	else if (torque > maxTorque)
	{
		motorSetTorque = maxTorque;
	}
	else
	{
		motorSetTorque = torque;
	}
	motorSetTorque = motorSetTorque * ctrlPossitive;
	if (isnan(motorSetTorque))
	{
		cout << motorName << "  set torque nan" << endl;
	}
	if (deforceFlag == 1)
	{
		motorSetTorque = 0;
	}
	cout << "max_T:   " <<maxTorque << endl;
	cout << "set_T:   " <<motorSetTorque << endl;
	motor->setTorque(motorSetTorque);
	//cout << ctrlPossitive << endl;
}

/**
 * @brief 获取电机力矩输出
 */
double MotorCtrl::getMotorTorque(void)
{
	double motorNowTorque = motor->getForceFeedback();
	cout<<motorName<<"T_now:  "<<motorNowTorque<<endl;
	return motorNowTorque;
}

/**
 * @brief 获取电机的反馈位置。
 * 此函数调用电机传感器以获取当前位置值。
 * 如果获取的位置为 NaN（不是一个数字），则记录警告。
 * 然后函数返回电机的反馈位置。
 * @return 电机的反馈位置。
 */
float MotorCtrl::getMotorFbPosition()
{
	motorSensor->getPositionValue();
	if (isnan(motorSensor->position))
	{
		ldg_warn(motorName + " position nan");
	}
	motorFbPosition = motorSensor->position;
	cout<<motorName<<"P_now:  "<<motorFbPosition<<endl;
	return motorFbPosition;
}

/**
 * @brief 获取电机的反馈速度。
 * 此函数调用 getMotorFbPosition() 函数以获取当前位置值。
 * 然后计算当前速度值，并记录当前时间。
 * 然后函数返回电机的反馈速度。
 * @return 电机的反馈速度。
 */
float MotorCtrl::getMotorFbSpeed()
{
	getMotorFbPosition();
	speedTime = titaClock;   //获取当前时间
	// cout<<"time :  "<<speedTime - speedTime_last<<endl;
	motorFbSpeed = (motorFbPosition - motorFbPosition_last) / (speedTime - speedTime_last);

	if (isnan(motorFbSpeed))
	{
		ldg_warn(motorName + " speed nan");
		if (isnan(motorFbSpeed_last))
		{
			return 0;
		}
		return motorFbSpeed_last;
	}
	if (isinf(motorFbSpeed))
	{
		ldg_warn(motorName + " speed inf");
		if (isinf(motorFbSpeed_last))
		{
			return 0;
		}
		return motorFbSpeed_last;
	}
	speedTime_last = speedTime; //记录上一次时间
	motorFbPosition_last = motorFbPosition;
	return motorFbSpeed;
}

/**
 * @brief 获取电机的反馈加速度。
 * 此函数调用 getMotorFbSpeed() 函数以获取当前速度值。
 * 然后计算当前加速度值，并记录当前时间。
 * 然后函数返回电机的反馈加速度。
 * @return 电机的反馈加速度。
 */
float MotorCtrl::getMotorFbAccelerate()
{
	getMotorFbSpeed();
	accTime = titaClock;
	motorFbAcc = (motorFbSpeed - motorFbSpeed_last) / (accTime - accTime_last);
	if (isnan(motorFbAcc))    //nan表示不是一个数字
	{ 
		ldg_warn(motorName + " acc nan");   
		return motorFbSpeed_last;
	}
	if (isinf(motorFbAcc))   //inf表示无穷大或无穷小
	{
		ldg_warn(motorName + " acc inf");
		return motorFbSpeed_last;
	}
	accTime_last = accTime;
	motorFbSpeed_last = motorFbSpeed;
	return motorFbAcc;
}

/**
 * @brief 设定电机速度
 * @param speed 速度值
 */
void MotorCtrl::setMotorSpeed(double speed)
{
	motor->setPosition(INFINITY);  // 设置为无限大表示速度控制模式
    motor->setVelocity(speed);   
}

void MotorCtrl::setMotorPosition(double position)
{
}



void MotorCtrl::setMotorMaxTorque(double maxT)
{
	maxTorque = maxT;
}

void MotorCtrl::setMotorPossitive(int8_t _p)
{
	ctrlPossitive = _p;
}
void MotorCtrl::feedbackPossitive(int8_t _p)
{
	motorSensor->isPossitive(_p);
}

/**
 * @brief 打印电机信息
 * 根据传入的消息类型打印电机的相关信息。
 * @param message 指定要打印的信息类型，可以是 "position"（位置）、"speed"（速度）或 "accelerate"（加速度）。
 * @note 该函数会根据不同的消息类型调用相应的函数获取电机反馈信息，并通过 data1 函数打印出来。
 */
void MotorCtrl::printMotorInfo(string message)
{
	if (message == "position")
	{
		getMotorFbPosition();
		data1((motorName + " position is "), motorFbPosition);
	}
	else if (message == "speed")
	{
		getMotorFbSpeed();
		data1((motorName + " speed is "), motorFbSpeed);
	}
	else if (message == "accelerate")
	{
		getMotorFbAccelerate();
		data1((motorName + " accelerate is "), motorFbAcc);
	}
}