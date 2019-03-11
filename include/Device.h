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
public:
	/**
	 * Конструктор устройства
	 * @param name Название утройства
	 */
	explicit Device(std::string name);

	/**
	 * Инициализация устройства
	 * @return Результат инициализации
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
