#include <bluetooth/Bluetooth.h>

#include <BLEDevice.h>

#include <utils/Log.h>

#define UUID_1 "7eea71e1-8bf4-44ce-ad37-06ef17092c27"
#define UUID_2 "110eedd3-721d-4ad4-9bcd-8006b7fc4bf9"

Bluetooth::Bluetooth() {
	logTrace("Bluetooth::Bluetooth start");
	BLEDevice::init("Isarithm");
	BLEServer *pServer = BLEDevice::createServer();
	BLEService *pService = pServer->createService(UUID_1);
	BLECharacteristic *pCharacteristic = pService->createCharacteristic(
			UUID_2,
			BLECharacteristic::PROPERTY_READ |
			BLECharacteristic::PROPERTY_WRITE
	);
	pCharacteristic->setValue("Isarithm online");
	pService->start();
	BLEAdvertising *pAdvertising = pServer->getAdvertising();
	pAdvertising->start();
	logTrace("Bluetooth::Bluetooth end");
}

bool Bluetooth::setCharacteristicValue(std::string characteristic, void* data, size_t size) {
	logTrace("Bluetooth::setCharacteristicValue start");
	// TODO: Имплементировать
	logTrace("Bluetooth::setCharacteristicValue end");
	return true;
}
