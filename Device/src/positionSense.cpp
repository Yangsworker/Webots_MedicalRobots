#include <Device/inc/positionSense.h>

positionSense::positionSense(string _sensorName)
{
	sensorName = _sensorName;
	position = 0;
	sensor = NULL;
	dataPossitive = 1;
}
void positionSense::SensorInit()
{
	sensor = new PositionSensor(sensorName);
	sensor->enable(timeStep);
}
void positionSense::getPositionValue()
{
	position = sensor->getValue() * dataPossitive;
	if (isnan(position))
	{
		
		//cout << "motor position nan" << endl;
	}
}
void positionSense::isPossitive(int8_t _p)
{
	dataPossitive = _p;
}