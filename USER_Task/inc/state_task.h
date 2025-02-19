#pragma once 
#include <user.h>
#include "Device/inc/motorCtrl.h"
#include <Device/inc/camera.h>
#include <Device/inc/distanceSense.h>
#include <Device/inc/gps.h>
#include <Device/inc/lidar.h>
#include <Device/inc/myImu.h>


class State{
    public:
    State(MotorCtrl * MW_L, MotorCtrl * MW_R);
    MotorCtrl * MW_L;  //左轮
    MotorCtrl * MW_R;  //右轮
    double speed_L = 0, speed_R = 0;  //左右轮速
    int count3 = 0;

    cameraSensor * camera_F;
    cameraSensor * camera_B;
    cameraSensor * camera_L;
    cameraSensor * camera_R;

    distanceSense * disSensor_top;

    GpsSense * gps;
    
    lidarSense * lidar;

    MyImu * myimu;

    bool wait_ten_seconds();  //State_1
    bool move_like8();        //State_2
    bool find_red();          //State_3
      void Adjust_Dir();   //根据不同摄像头检测红色方位调整正方向
    bool send_pack();         //State_4
    bool back_one_second();   //State_5
    bool back_origin();       //State_6   返回原点



    bool movelike8_turnround = 0;  //是否换向（用于8字行走）

    void getSensorValue_500hz(void);   //获取所有传感器数据
    void getSensorValue_100hz(void);


};
