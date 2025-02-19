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
    int count = 0;
    static int last_state_count = 0;
//以下为执行状态机
    switch (state_count)
    {
    case 1:
        if(state->wait_ten_seconds())   //等待10秒
        {
            state_count = 2;
        }
        if(state->disSensor_top->position < 100)
        {
            state_count = 3;
        }
        count = 1;
        break;
    case 2:
        if(state->move_like8())         //8字行走
        {
            state_count = 1;           
        }
        count = 2;
        break;
    case 3:
        if(state->find_red())           //寻找红色
        {
            state_count = 4;
        }
        if(state->lidar->mindisPosition < 0.15)
        {
            state_count = 5;
            last_state_count = 3;
        }
        count = 3;
        break;
    case 4:
        state->send_pack();          //运输快递
        if(state->disSensor_top->position == 1000)
        {
            state_count = 6;
        }
        count = 4;
        break;
    case 5:
        if(state->back_one_second())    //回退一秒
        {
            state_count = last_state_count;
        }
        count = 5;
        break;
    case 6: 
        if(state->back_origin())        //返回原点
        {
            state_count = 2;
        }
        if(state->lidar->mindisPosition < 0.15)
        {
            state_count = 5;
            last_state_count = 6;
        }
        count = 6;
        break;
    default:
        break;
    }
    //cout<<"state_count: "<<state_count<<" " <<count<<" dis: "<<state->disSensor_top->position<<"    "<<state->lidar->midValue<<endl;
}


/**
 * @brief 底盘控制函数
*/
void Chassis::State_control(void)
{
    switch (state_count)
    {
    case 1:   //等待10秒
        state->wait_ten_seconds();   
        break;
    case 2:   //8字行走
        state->move_like8();         
        break;
    case 3:    //寻找红色
        state->find_red();          
        break;
    case 4:    //运输快递
        state->send_pack();         
        break;
    case 5:    //回退一秒
        state->back_one_second();    
        break;
    case 6:   //返回原点
        state->back_origin();        
        break;
    default:
        break;
    }
}


