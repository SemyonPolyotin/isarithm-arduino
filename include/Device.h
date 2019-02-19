#pragma once

#include <string>

#include <finger/Finger.h>
#include <bluetooth/Bluetooth.h>
#include <accelerometer/Accelerometer.h>
#include <activity/ActivityStorage.h>

/**
 * Класс описания состояния устройства
 */
class Device {
private:
public:
	explicit Device(std::string name);

	/**
	 * Инициализация устройства
	 */
	bool Init();

	/**
	 * Обновление устройства
	 */
	void Update();

private:
	// Имя устройства
	std::string name;
	// Палец
	Finger* pFinger;
	// Bluetooth
	Bluetooth* pBluetooth;
	// Акселерометр
	Accelerometer* pAccelerometer;
	// Данные активностей
	ActivityStorage* pActivityStorage;

};
