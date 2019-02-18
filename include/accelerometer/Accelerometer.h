#pragma once

#include <I2Cdev.h>
#include <MPU6050.h>

class Accelerometer {
public:
	Accelerometer();

	void update();

private:
	MPU6050 accelgyro;

	int16_t ax, ay, az;
	int16_t gx, gy, gz;

};
