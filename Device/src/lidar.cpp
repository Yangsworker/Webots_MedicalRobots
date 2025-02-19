#include <Device/inc/lidar.h>

lidarSense::lidarSense(string _sensorName)
{
	sensorName = _sensorName;
	sensor = NULL;
}
void lidarSense::SensorInit()
{
	sensor = new Lidar(sensorName);
	sensor->enable(timeStep);
	sensor->enablePointCloud();  // 启用点云数据
}
void lidarSense::getPositionValue()
{
	mindisPosition = 0.5;   mindisNum = 130;
	lidar_values = sensor->getRangeImage();
	for(int a = 0; a < 128; a++)
	{
		if(lidar_values[a] < mindisPosition)
		{
			mindisPosition = lidar_values[a];
			mindisNum = a;
		}
	}
	cout << mindisPosition << " " << mindisNum << endl;
    cout << lidar_values[20] << " " << lidar_values[50] << " " << lidar_values[80] << " " << lidar_values[100] << " " << lidar_values[110] << " " << lidar_values[120] << " " << endl;
}
