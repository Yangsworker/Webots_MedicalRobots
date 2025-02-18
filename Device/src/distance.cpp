#include <Device/inc/distance.h>

Distance::Distance(string _DisName)
{
    sensorName = _DisName;
}
void Distance::sensorInit()
{
    disSensor = new DistanceSensor(sensorName);
    disSensor->enable(timeStep);        
}
void Distance::getData()
{
    distance = disSensor->getValue();
}