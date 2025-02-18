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
    void chassis_control(void);
};
extern Chassis chassis;
void chassis_task();

