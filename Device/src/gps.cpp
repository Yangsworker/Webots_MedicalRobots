#include <Device/inc/gps.h>

GpsSense::GpsSense(string _sensorName)
{
	sensorName = _sensorName;
	position = 0;
	sensor = NULL;
}
void GpsSense::SensorInit()
{
	sensor = new GPS(sensorName);
	sensor->enable(timeStep);
}
void GpsSense::getGPSValue()
{
	position = sensor->getValues();
    cout << position[0] << ',' << position[1] << ',' << position[2] << endl;
}

