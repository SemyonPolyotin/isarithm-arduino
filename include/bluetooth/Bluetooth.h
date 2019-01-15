#pragma once

#include <map>

/**
 * Класс для работы с Bluetooth соединениями
 */
class Bluetooth {
public:
	Bluetooth();

	bool setCharacteristicValue(std::string characteristic, void* data, size_t size);

private:
	// Ассоциативный массив характеристик
	std::map<std::string, std::string> characteristics;
};
