#include <utility>

#include <bluetooth/Bluetooth.h>

#include <utils/Log.h>

// Состояние наличия подключения
bool bIsClientConnected = false;

void ServerCallbacks::onConnect(BLEServer* pServer) {
	bIsClientConnected = true;
}

void ServerCallbacks::onDisconnect(BLEServer* pServer) {
	bIsClientConnected = false;
}

bool Bluetooth::IsConnected() {
	return bIsClientConnected;
}

#define BLE_UUID_SERVICE_BATTERY BLEUUID((uint16_t) 0x180F)
#define BLE_UUID_CHARACTERISTIC_BATTERY_LEVEL BLEUUID((uint16_t) 0x2A19)

#define BLE_UUID_SERVICE_DEVICE_INFORMATION BLEUUID((uint16_t) 0x180A)
#define BLE_UUID_CHARACTERISTIC_MANUFACTURER_NAME_STRING BLEUUID((uint16_t) 0x2A29)
#define BLE_UUID_CHARACTERISTIC_MODEL_NUMBER_STRING BLEUUID((uint16_t) 0x2A24)

#define BLE_UUID_SERVICE_USER_DATA BLEUUID((uint16_t) 0x181C)
#define BLE_UUID_CHARACTERISTIC_FIRST_NAME BLEUUID((uint16_t) 0x2A8A)
#define BLE_UUID_CHARACTERISTIC_LAST_NAME BLEUUID((uint16_t) 0x2A8A)
#define BLE_UUID_CHARACTERISTIC_EMAIL_ADDRESS BLEUUID((uint16_t) 0x2A87)

#define UUID_SERVICE "7eea71e1-8bf4-44ce-ad37-06ef17092c27"
#define UUID_CHAR_STATUS "3c720a95-549e-46be-8a4a-3a5b8c0517fb"
#define UUID_CHAR_SERVO_COMMANDS "110eedd3-721d-4ad4-9bcd-8006b7fc4bf9"

Bluetooth::Bluetooth() {
	logTrace("Bluetooth::Bluetooth start");
	BLEDevice::init("Isarithm");
	BLEServer* pServer = BLEDevice::createServer();
	pServer->setCallbacks(new ServerCallbacks());

	// Device info
	BLEService* pDeviceService = pServer->createService(BLE_UUID_SERVICE_DEVICE_INFORMATION);
	pDeviceService->createCharacteristic(BLE_UUID_CHARACTERISTIC_MANUFACTURER_NAME_STRING,
										 BLECharacteristic::PROPERTY_READ
	)->setValue("Semyon Polyotin");
	pDeviceService->createCharacteristic(BLE_UUID_CHARACTERISTIC_MODEL_NUMBER_STRING,
										 BLECharacteristic::PROPERTY_READ
	)->setValue("Isarithm");
	pDeviceService->start();

	// Battery service
	BLEService* pBatteryService = pServer->createService(BLE_UUID_SERVICE_BATTERY);
	uint8_t val = 100;
	pBatteryService->createCharacteristic(BLE_UUID_CHARACTERISTIC_BATTERY_LEVEL,
										  BLECharacteristic::PROPERTY_READ
	)->setValue(&val, 1);
	pBatteryService->start();

	// User data
	BLEService* pUserDataService = pServer->createService(BLE_UUID_SERVICE_USER_DATA);
	pUserDataService->createCharacteristic(BLE_UUID_CHARACTERISTIC_FIRST_NAME,
										   BLECharacteristic::PROPERTY_READ |
										   BLECharacteristic::PROPERTY_WRITE);
	pUserDataService->createCharacteristic(BLE_UUID_CHARACTERISTIC_LAST_NAME,
										   BLECharacteristic::PROPERTY_READ |
										   BLECharacteristic::PROPERTY_WRITE);
	pUserDataService->createCharacteristic(BLE_UUID_CHARACTERISTIC_EMAIL_ADDRESS,
										   BLECharacteristic::PROPERTY_READ |
										   BLECharacteristic::PROPERTY_WRITE);
	pUserDataService->start();

	// Custom service
	BLEService* pCustomService = pServer->createService(UUID_SERVICE);
	this->statusCharacteristic = pCustomService->createCharacteristic(UUID_CHAR_STATUS,
																	  BLECharacteristic::PROPERTY_READ |
																	  BLECharacteristic::PROPERTY_WRITE);
	this->statusCharacteristic->setValue("Isarithm online");
	this->servoCharacteristic = pCustomService->createCharacteristic(UUID_CHAR_SERVO_COMMANDS,
																	 BLECharacteristic::PROPERTY_READ |
																	 BLECharacteristic::PROPERTY_WRITE);
	pCustomService->start();

	BLEAdvertising* pAdvertising = pServer->getAdvertising();
	pAdvertising->start();
	logTrace("Bluetooth::Bluetooth end");
}

bool Bluetooth::SetCharacteristicValue(std::string name, std::string data) {
	logTrace("Bluetooth::SetCharacteristicValue start");
	servoCharacteristic->setValue(std::move(data));
	logTrace("Bluetooth::SetCharacteristicValue end");
	return true;
}

std::string Bluetooth::GetCharacteristicValue(std::string name) {
	std::string val = servoCharacteristic->getValue();
	servoCharacteristic->setValue("");
	return val;
}
