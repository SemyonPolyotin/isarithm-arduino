#pragma once

#include <I2Cdev.h>
#include <MPU6050.h>

/**
 * Данные акселерометра
 */
struct AccelerometerData {
	// Ускорение
	int16_t ax, ay, az;
	// Наклон
	int16_t gx, gy, gz;
};

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

	AccelerometerData GetData();

	static AccelerometerData GetDefaultData();

private:
	/**
	 * Акселерометр
	 */
	MPU6050 mpu;

	/**
	 * Данные акселерометра
	 */
	AccelerometerData data;

};
