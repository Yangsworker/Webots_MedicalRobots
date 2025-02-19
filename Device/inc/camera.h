#pragma once
#include <user.h>
#include <webots/Camera.hpp>

#define red_threshold 50
#define green_threshold 30
#define blue_threshold 30

using namespace webots;
class cameraSensor
{
private:
    /* data */
public:
    cameraSensor(string _cameraName);
    Camera *camera;

    const unsigned char *image;
    int width = 0, height = 0;  //图像大小

    int sum_x = 0, sum_y = 0, count = 0;   //红色像素坐标和
    int center_x = 0, center_y = 0;  //红色区域质心
    int error_x = 0, error_y = 0;  //偏差

    string cameraName;
    void CameraInit();
    void getCameraImage();
};



