#pragma once

#include <string>

#include <finger/Finger.h>
#include <bluetooth/Bluetooth.h>

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
	bool init();
	/**
	 * Обновление устройства
	 */
	void update();

private:
	// Имя устройства
	std::string name;
	// Палец
	Finger* pFinger;
	// Bluetooth
	Bluetooth* pBluetooth;
};
