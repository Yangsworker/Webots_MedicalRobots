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
	mindisPosition = 0.5;     mindisNum = 130;
	mindisPosition_2 = 0.5;   mindisNum_2 = 130;
	lidar_values = sensor->getRangeImage();
	//获取中间值
	midValue = lidar_values[64];
	//获取最小值
	for(int a = 0; a < 128; a++)
	{
		if(lidar_values[a] < mindisPosition)
		{
			mindisPosition = lidar_values[a];
			mindisNum = a;
		}
	}
	//获取第二最小值
	for(int i = 0; i < 40; i++)
	{
		if(lidar_values[i] < mindisPosition_2)
		{
			mindisPosition_2 = lidar_values[i];
			mindisNum_2 = i;
		}
	}
	for(int p = 88; p < 128; p++)
	{
		if(lidar_values[p] < mindisPosition_2)
		{
			mindisPosition_2 = lidar_values[p];
			mindisNum_2 = p;
		}
	}
	//mindisPosition_2
	//cout << mindisPosition_2 << " " << mindisNum_2 << endl;
    //cout << lidar_values[20] << " " << lidar_values[50] << " " << lidar_values[80] << " " << lidar_values[100] << " " << lidar_values[110] << " " << lidar_values[120] << " " << endl;
}
