#pragma once

#include <map>
#include <BLEDevice.h>

/**
 * Класс для работы с Bluetooth соединениями
 */
class Bluetooth {
public:
	Bluetooth();

	bool SetCharacteristicValue(std::string name, std::string data);

	std::string GetCharacteristicValue(std::string name);

private:
	// Ассоциативный массив характеристик
	std::map<std::string, BLECharacteristic*> characteristics;

	BLECharacteristic* servoCharacteristic;

};
