#pragma once 
#include <user.h>
#include "Device/inc/motorCtrl.h"
#include "USER_Task/inc/state_task.h"

class Chassis{
    public:
    Chassis();
    State * state;
    MotorCtrl * MW_L;  //左轮
    MotorCtrl * MW_R;  //右轮
    void chassis_run(void);
    void State_control(void);
    int state_count = 2;  //状态计数
};
extern Chassis chassis;
void chassis_task();

