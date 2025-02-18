#include <Device/inc/camera.h>

 cameraSensor::cameraSensor(string _cameraName)
{
	cameraName = _cameraName;
	camera = NULL;
}
void cameraSensor::CameraInit()
{
	camera = new Camera(cameraName);
	camera->enable(timeStep);
}


