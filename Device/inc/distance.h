#pragma once
#include <user.h>
#include <iostream>
#include <webots/DistanceSensor.hpp>
using namespace webots;
class Distance
{
private:
    /* data */
public:
    Distance(string _DisName);
    string sensorName;
    DistanceSensor *disSensor;
    void getData();
    double distance;
    void sensorInit();
};




