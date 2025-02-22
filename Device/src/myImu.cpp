#include <Device/inc/myImu.h>

MyImu::MyImu(string _imuName, string _gyroName)
{
    imu = NULL;
    imuName = _imuName;
    gyroName = _gyroName;
    rollGyro_last = rollGyro = 0;
    pitchGyro_last = pitchGyro = 0;
    yawGyro_last = yawGyro = 0;
}
void MyImu::imuInit()
{
    imu = new InertialUnit(imuName);
    imu->enable(timeStep);
    gyro = new Gyro(gyroName);
    gyro->enable(timeStep);
}
void MyImu::getImuData()
{
    //getGyroData();
    roll = imu->getRollPitchYaw()[0] * dataPossitive[ROLL];
    pitch = imu->getRollPitchYaw()[1] * dataPossitive[PITCH];
    yaw = imu->getRollPitchYaw()[2] * dataPossitive[YAW];
  if((yaw_last > 3.0f) && (yaw < -3.0f))
  {
    quanshu++;
  }
  if((yaw_last < -3.0f) && (yaw > 3.0f))
  {
    quanshu--;
  }
    imuTime = titaClock;
    rollSpeed = (roll - roll_last) / (imuTime - imuTime_last);
    pitchSpeed = (pitch - pitch_last) / (imuTime - imuTime_last);
    yawSpeed = (yaw - yaw_last) / (imuTime - imuTime_last);
    imuTime_last = imuTime;
    if (isnanf(roll) || isnanf(pitch) || isnanf(yaw))
    {
        cout << "motor imu nan" << endl;
    }
    if (isnanf(rollSpeed) || isnanf(pitchSpeed) || isnanf(yawSpeed))
    {
        cout << "motor imuSpeed nan" << endl;
    }
    roll_last = roll;
    pitch_last = pitch;
    yaw_last = yaw;
}
void MyImu::getGyroData()
{
    rollGyro = gyro->getValues()[0] * dataPossitive[ROLL];
    pitchGyro = gyro->getValues()[1] * dataPossitive[PITCH];
    yawGyro = gyro->getValues()[2] * dataPossitive[YAW];
}
void MyImu::gyroCalculate()
{
    getGyroData();
    if(!gyroInitFlag)
    {
        rollAngleOfGyro = roll;
        pitchAngleOfGyro = pitch;
        yawAngleOfGyro = yaw;
        gyroInitFlag = true;
    }
    gyroTime = titaClock;
    double timeErr = gyroTime - gyroTime_last;
    gyroTime_last = gyroTime;
    rollAngleOfGyro = rollAngleOfGyro + (rollGyro_last * timeErr);
    pitchAngleOfGyro = pitchAngleOfGyro + (pitchGyro_last * timeErr);
    yawAngleOfGyro = yawAngleOfGyro + (yawGyro_last * timeErr);
    rollGyro_last = rollGyro;
    pitchGyro_last = pitchGyro;
    yawGyro_last = yawGyro;
}
void MyImu::isPossitive(uint8_t axis, int8_t _p)
{
    if(axis == YAW)
    {
        dataPossitive[YAW] = _p;
    }
    if(axis == PITCH)
    {
        dataPossitive[PITCH] = _p;
    }
    if(axis == ROLL)
    {
        dataPossitive[ROLL] = _p;
    }
}
void MyImu::pirntImuMessege(char16_t _r)
{
    getImuData();
    if (_r == 'r')
    {
        data1(imuName, roll);
    }
    else if (_r == 'y')
    {
        data1(imuName, yaw);
    }
    else if (_r == 'p')
    {
        data1(imuName, pitch);
    }
}