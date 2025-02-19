#pragma once
#include <user.h>
#include <webots/Camera.hpp>

using namespace webots;
class cameraSensor
{
private:
    /* data */
public:
    cameraSensor(string _cameraName);
    Camera *camera;

    const unsigned char *image;

    string cameraName;
    void CameraInit();
};



