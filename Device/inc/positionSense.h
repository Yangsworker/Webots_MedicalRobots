#pragma once
#include <webots/PositionSensor.hpp>
#include <user.h>

using namespace webots;
class positionSense
{
private:
    /* data */
public:
    positionSense(string _sensorName);
    string sensorName;
    void SensorInit();
    PositionSensor *sensor;
    double position;
    void getPositionValue();
    int8_t dataPossitive = 1;
    void isPossitive(int8_t _p);
};
