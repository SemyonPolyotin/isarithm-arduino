#pragma once

#include <map>
#include <BLEDevice.h>

/**
 * Класс для обозначения состояния соединения
 */
class ServerCallbacks : public BLEServerCallbacks {
	void onConnect(BLEServer* pServer) override;;

	void onDisconnect(BLEServer* pServer) override;

};

/**
 * Класс для работы с Bluetooth соединениями
 */
class Bluetooth {
public:
	Bluetooth();

	bool SetCharacteristicValue(std::string name, std::string data);

	std::string GetCharacteristicValue(std::string name);

	static bool IsConnected();

private:
	// Ассоциативный массив характеристик
	std::map<std::string, BLECharacteristic*> characteristics;

	BLECharacteristic* statusCharacteristic;
	BLECharacteristic* servoCharacteristic;

};
