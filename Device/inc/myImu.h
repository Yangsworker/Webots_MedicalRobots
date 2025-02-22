#pragma once
#include <user.h>
#include <webots/InertialUnit.hpp>
#include <webots/Gyro.hpp>
#include <iostream>
using namespace webots;
enum ImuAxis
{
    ROLL = 0U,
    PITCH,
    YAW
};
class MyImu
{
private:
    /* data */
public:
    MyImu(string _imuName,string _gyroName);
    string imuName;
    string gyroName;
    InertialUnit *imu;
    Gyro *gyro;
    double imuTime, imuTime_last;
    double gyroTime,gyroTime_last;
    void imuInit();
    double roll, roll_last, rollSpeed;
    double yaw, yaw_last, yawSpeed;
    double pitch, pitch_last, pitchSpeed;
    double rollGyro,pitchGyro,yawGyro,rollGyro_last,pitchGyro_last,yawGyro_last;
    double rollAngleOfGyro,pitchAngleOfGyro,yawAngleOfGyro;
    void getImuData();
    void getGyroData();
    void gyroCalculate();
    int quanshu = 0;
    int8_t dataPossitive[3] = {1,1,1};
    bool gyroInitFlag = false;
    void isPossitive(uint8_t axis, int8_t _p);
    void pirntImuMessege(char16_t _r);
};
