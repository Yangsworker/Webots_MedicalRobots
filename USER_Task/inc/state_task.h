#pragma once 
#include <user.h>
#include "Device/inc/motorCtrl.h"
#include <Device/inc/camera.h>
#include <Device/inc/distanceSense.h>
#include <Device/inc/gps.h>

class State{
    public:
    State(MotorCtrl * MW_L, MotorCtrl * MW_R);
    MotorCtrl * MW_L;  //左轮
    MotorCtrl * MW_R;  //右轮

    cameraSensor * camera_F;
    cameraSensor * camera_B;
    cameraSensor * camera_L;
    cameraSensor * camera_R;

    distanceSense * disSensor_top;

    GpsSense * gps;


    bool wait_ten_seconds();  //State_1
    bool move_like8();        //State_2
    bool find_red();          //State_3
    bool send_pack();         //State_4
    bool back_one_second();   //State_5
    bool back_origin();       //State_6   返回原点



    bool movelike8_turnround = 0;  //是否换向（用于8字行走）




};
