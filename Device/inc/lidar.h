#pragma once
#include <webots/Lidar.hpp>
#include <user.h>

using namespace webots;
class lidarSense
{
private:
    /* data */
public:
    lidarSense(string _sensorName);
    string sensorName;
    void SensorInit();
    Lidar *sensor;
    void getPositionValue();
    const float *lidar_values;
    int num_beams = 128;  //激光雷达数据个数
    float mindisPosition = 0;
    int mindisNum = 0;  //最近激光条数
};
