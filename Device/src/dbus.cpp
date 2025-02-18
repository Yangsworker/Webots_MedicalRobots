#include "dbus.h"
#include <string>
#include <iostream>
#include <user.h>
#include <cstring>
using namespace std;
RemoteCtrl RC;
uint8_t deforceFlag = 1;
RemoteCtrl::RemoteCtrl()
{
}
RemoteCtrl::~RemoteCtrl()
{
}


void RemoteCtrl::RC_init(void)
{
   webots::Keyboard *keyboard = new webots::Keyboard();
   // 启用键盘输入
   keyboard->enable(timeStep);
}


using namespace RCS;
// 数据处理
void RemoteCtrl::handleData()
{
        key.A = (rc == 'A');
        key.B = (rc == 'B');
        key.C = (rc == 'C');
        key.D = (rc == 'D');
        key.F = (rc == 'F');
        key.G = (rc == 'G');
        key.H = (rc == 'H');
        key.I = (rc == 'I');
        key.J = (rc == 'J');
        key.K = (rc == 'K');
        key.L = (rc == 'L');
        key.M = (rc == 'M');
        key.N = (rc == 'N');
        key.O = (rc == 'O');
        key.P = (rc == 'P');
        key.Q = (rc == 'Q');
        key.R = (rc == 'R');
        key.S = (rc == 'S');
        key.Y = (rc == 'T');
        key.U = (rc == 'U');
        key.V = (rc == 'V');
        key.W = (rc == 'W');
        key.X = (rc == 'X');
        key.Y = (rc == 'Y');
        key.Z = (rc == 'Z');
        key.Down = (rc == webots::Keyboard::DOWN);
        key.Up   = (rc == webots::Keyboard::UP);

    memcpy(&lastKey, &key, sizeof(key));
}

/**
 * @brief 任务调度
 * @note 通过遥控器指令执行相关任务的挂起和恢复
 * @warning 脱力控制也在这边，注意一下
 */

void RCtaskSchedule()
{
    RC.rc = RC.keyboard->getKey();  // 获取键盘输入
    RC.handleData();
    if (RC.key.Down)
    {
        deforceFlag = 1;
    }
    if(RC.key.Up)
    {
        deforceFlag = 0;
    }
}