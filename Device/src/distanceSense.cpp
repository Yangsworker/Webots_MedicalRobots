#include <Device/inc/distanceSense.h>

distanceSense::distanceSense(string _sensorName)
{
	sensorName = _sensorName;
	position = 0;
	sensor = NULL;
}
void distanceSense::SensorInit()
{
	sensor = new DistanceSensor(sensorName);
	sensor->enable(timeStep);
}
void distanceSense::getPositionValue()
{
	position = sensor->getValue();
    cout << position << endl;
	if (isnan(position))
	{	
		cout << "motor position nan" << endl;
	}
}
