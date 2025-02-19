#include "USER_Task/inc/state_task.h"
#include <Device/inc/dbus.h>


State::State(MotorCtrl * MW_L, MotorCtrl * MW_R):MW_L(MW_L), MW_R(MW_R)
 {
    camera_F = new cameraSensor("camera_F");
    camera_B = new cameraSensor("camera_B");
    camera_L = new cameraSensor("camera_L");
    camera_R = new cameraSensor("camera_R"); 
    camera_F->CameraInit();
    camera_B->CameraInit();
    camera_L->CameraInit();
    camera_R->CameraInit();

    disSensor_top = new distanceSense("dis_sensor_top");
    disSensor_top->SensorInit();

    gps = new GpsSense("gps");
    gps->SensorInit();
  }


/**
 * @brief State1 等待10秒
*/
bool State::wait_ten_seconds() 
{
    static int count = 0;
    if (count < 1000)
    {
        count++;
        return false;
    }
    else
    {
        count = 0;
        return true;
    }
}

/**
 * @brief State2 8字形运动
 * @note 使用差速效果
*/
bool State::move_like8()
{
   int speed_L = 0, speed_R = 0; 
    static int count2 = 0;   //计数
    count2++;
    if(ABS(gps->position[0]) < 0.03 && ABS(gps->position[1]) < 0.03 && count2 > 200)   //回到原地
    {
     count2 = 0;
     movelike8_turnround = !movelike8_turnround;
    }
    speed_L = !movelike8_turnround ? 6 : 3;
    speed_R = !movelike8_turnround ? 3 : 6;
    cout<<speed_R<<"   "<<speed_L<<"   "<<count2<<"  "<<movelike8_turnround<<endl;  
   MW_L->setMotorSpeed(speed_L);
   MW_R->setMotorSpeed(speed_R);
   return true;
}

/**
 * @brief State3 寻找红色物体
*/
bool State::find_red()
{
    static int count = 0;
    if (count < 1000)
    {
        count++;
        return false;
    }
    else
    {
        count = 0;
        return true;
    }
}

/**
 * @brief State4 运输快递
*/
bool State::send_pack()
{
    static int count = 0;
    if (count < 1000)
    {
        count++;
        return false;
    }
    else
    {
        count = 0;
        return true;
    }
}

/**
 * @brief State5 回退一秒
*/
bool State::back_one_second()
{
    static int count = 0;
    if (count < 1000)
    {
        count++;
        return false;
    }
    else
    {
        count = 0;
        return true;
    }
}

/**
 * @brief State6 返回原点
*/
bool State::back_origin()
{
    static int count = 0;
    if (count < 1000)
    {
        count++;
        return false;
    }
    else
    {
        count = 0;
        return true;
    }
}
