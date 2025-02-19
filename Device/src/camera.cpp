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

/// @brief 100hz执行
void cameraSensor::getCameraImage()
{
	image = camera->getImage();
	width = camera->getWidth();
    height = camera->getHeight();

	sum_x = 0; sum_y = 0; count = 0;  //init
	center_x = 0; center_y = 0;
	error_x = 0; error_y = 0;

	 // 遍历图像中的每一个像素，进行颜色识别
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        int red = camera->imageGetRed(image, width, x, y);
        int green = camera->imageGetGreen(image, width, x, y);
        int blue = camera->imageGetBlue(image, width, x, y);
    //  if(x == 32 && y == 32)
	//  {
	// 	 cout << "red: " << red << " green: " << green << " blue: " << blue << endl;
	//  }
        // 判断该像素是否为红色
        if (red > red_threshold && green < green_threshold && blue < blue_threshold) {
          // 累加红色区域的坐标
          sum_x += x;
          sum_y += y;
          count++;
        }
      }
    }

	if (count > 0) {
      // 计算红色区域的质心（即重心）
      center_x = sum_x / count;
      center_y = sum_y / count;
      // 计算偏差
      error_x = center_x - width / 2;  // 计算红色区域中心与图像中心的偏差
      error_y = center_y - height / 2;
    }
//cout << "error_x: " << error_x <<"  error_y: "<<error_y <<" center_x: " << center_x << " center_y: " << center_y << endl;
}




   

