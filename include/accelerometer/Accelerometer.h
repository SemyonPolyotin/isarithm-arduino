#pragma once

#include <I2Cdev.h>
#include <MPU6050.h>

class Accelerometer {
public:
	Accelerometer();

	/**
	 * Инициализация акселерометра
	 * @return Результат инициализации
	 */
	bool Init();

	/**
	 * Обновление состояния акселерометра
	 */
	void Update();

private:
	MPU6050 mpu;

	// Ускорение
	int16_t ax, ay, az;
	// Наклон
	int16_t gx, gy, gz;

};
