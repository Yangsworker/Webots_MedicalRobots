#pragma once
#include <webots/GPS.hpp>
#include <user.h>

using namespace webots;
class GpsSense
{
private:
    /* data */
public:
    GpsSense(string _sensorName);
    string sensorName;
    void SensorInit();
    GPS *sensor;
    const double* position;
    void getGPSValue();
};
