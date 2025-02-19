#include "USER_Task/inc/chassis_task.h"
#include "Device/inc/myImu.h"
#include <Device/inc/dbus.h>
#include <Device/inc/positionSense.h>
#include <webots/PositionSensor.hpp>


/**
 * @brief 构造函数，初始化左右轮电机及传感器
*/
Chassis::Chassis()
{
    MW_L = new MotorCtrl("MW_L","PW_L");
    MW_R = new MotorCtrl("MW_R","PW_R");
    state = new State(MW_L, MW_R);
    MW_L->motorInit();
    MW_R->motorInit();
}

/**
 * @brief 底盘运行总函数
*/
void Chassis::chassis_run(void)
{
    //MW_L->getMotorFbPosition();
    //MW_R->getMotorFbPosition();
    //state->move_like8();
    state->find_red();
    //state->back_one_second();
}


/**
 * @brief 底盘控制函数
*/
void Chassis::chassis_control(void)
{
    // MW_L->setMotorSpeed(1);
    // MW_R->setMotorSpeed(1);
}


