#pragma once
#include <webots/DistanceSensor.hpp>
#include <user.h>

using namespace webots;
class distanceSense
{
private:
    /* data */
public:
    distanceSense(string _sensorName);
    string sensorName;
    void SensorInit();
    DistanceSensor *sensor;
    double position;    //获取的传感器值
    void getPositionValue();
};
