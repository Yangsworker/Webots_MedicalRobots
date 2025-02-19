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

    lidar = new lidarSense("lidar");
    lidar->SensorInit();
  }


void State::getSensorValue_500hz()
{   
    disSensor_top->getPositionValue();
    gps->getGPSValue();
}
/// @brief 100hz执行，减小cpu计算负担
void State::getSensorValue_100hz()
{
    camera_F->getCameraImage();
    camera_B->getCameraImage();
    camera_L->getCameraImage();
    camera_R->getCameraImage();

    lidar->getPositionValue();
}



/**
 * @brief State1 等待10秒,500hz执行,count阈值为5000
*/
bool State::wait_ten_seconds() 
{
    static int count = 0;
    if (count < 5000)
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
    static int count2 = 0;   //计数
    count2++;
    if(ABS(gps->position[0]) < 0.03 && ABS(gps->position[1]) < 0.03 && count2 > 200)   //回到原地
    {
     count2 = 0;
     movelike8_turnround = !movelike8_turnround;
    }
    speed_L = !movelike8_turnround ? 6 : 3;
    speed_R = !movelike8_turnround ? 3 : 6;
//    cout<<speed_R<<"   "<<speed_L<<"   "<<count2<<"  "<<movelike8_turnround<<endl;  
    MW_L->setMotorSpeed(speed_L);
    MW_R->setMotorSpeed(speed_R);
    return true;
}

/**
 * @brief State3 寻找红色物体
*/
int lostFlag = 0;
bool State::find_red()
{
    if(camera_F->center_x == 0)   //前置摄像头未发现红色才执行换向操作
    {
        Adjust_Dir();   //探索寻找红色
        if(lidar->mindisPosition < 0.35)    //前摄像头未发现红色，启用全避障
        {
            int error = lidar->mindisNum - 64;
            if(error <= 0)
            {
                error += 70;
            }
            else
            {
                error -= 70;
             }
            error = LIMIT(error, -60, 60);
            speed_L = -4 + error * 0.09; 
            speed_R = -4 - error * 0.09; 
        }
    }
    else   
    {
        if(lidar->mindisPosition_2 < 0.35)    
        {
            int error = lidar->mindisNum_2 - 64;
            if(error <= 0)
            {
                error += 70;
            }
            else
            {
                error -= 70;
             }
            error = LIMIT(error, -50, 50);
            speed_L = -4 + error * 0.09; 
            speed_R = -4 - error * 0.09; 
        }
        else
        {
            speed_L = -4 + camera_F->error_x * 0.05;
            speed_R = -4 - camera_F->error_x * 0.05;
        }
        count3 = 0;      //重置其他摄像头检测红色计数
    }
    MW_L->setMotorSpeed(speed_L);
    MW_R->setMotorSpeed(speed_R);
 //   cout <<camera_F->center_x<<" "<<camera_B->center_x<<" "<<camera_L->center_x<<" "<<camera_R->center_x<<endl;
 //   cout<<speed_R<<"   "<<speed_L<<endl;
    return true;
}
/// @brief 根据不同摄像头检测红色方位调整正方向
void State::Adjust_Dir()
{
    if((camera_B->center_x != 0) || (camera_L->center_x != 0) || (camera_R->center_x != 0))
    {
        count3++;
    }
    if(count3 > 10)
    {
        if(camera_B->center_x)
        {
            speed_L = 2, speed_R = -2;    //原地右转
        }
        else if(camera_R->center_x)
        {
            speed_L = -2, speed_R = 2;    //原地右转
        }
        else if(camera_L->center_x)
        {
            speed_L = 2, speed_R = -2;    //原地左转
        }
    }
    else
    {
        speed_L = -4, speed_R = -4;    //旁摄像头未发现红色---直走
    }
    cout << count3 << endl;
}



/**
 * @brief State4 运输快递
 * @note 速度为0,等待包裹取出
*/
bool State::send_pack()
{
    speed_L = 0; speed_R = 0;
    MW_L->setMotorSpeed(speed_L);
    MW_R->setMotorSpeed(speed_R);
    return true;
}

/**
 * @brief State5 回退一秒
 * @note 500hz执行,count阈值为500
*/
bool State::back_one_second()
{
    // static int count5 = 0;
    // if (count5 < 500)
    // {
    //     speed_L = 0; speed_R = 0;
    //     MW_L->setMotorSpeed(speed_L);
    //     MW_R->setMotorSpeed(speed_R);
    //     count5++;
    //     return false;
    // }
    // else
    // {
    //     count5 = 0;
    //     return true;
    // }
    MW_L->setMotorSpeed(speed_L);
    MW_R->setMotorSpeed(speed_R);
    return true;
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
