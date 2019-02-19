#include <Device.h>

#include <esp32-hal.h>

#include <utils/Log.h>

#define LED_PIN 2
bool blinkState = false;

Device::Device(std::string name) {
	logTrace("Device::Device start");
	this->name = name;
	logInfo("Initializing device " + name);
	delay(2000);
}

bool Device::Init() {
	logDebug("Device::Init start");
	// Ининциализация пальца
	pFinger = new Finger();
	if (!pFinger->Init()) {
		logError("Finger initialization failed");
		return false;
	}
	// Инициализация Bluetooth
	pBluetooth = new Bluetooth();
	// Инициализация акселерометра
	pAccelerometer = new Accelerometer();
	if (!pAccelerometer->Init()) {
		logError("Accelerometer initialization failed");
		return false;
	}
	// Инициализация хранения активностей
	pActivityStorage = new ActivityStorage();
	if (pActivityStorage->Init()) {
		logError("ActivityStorage initialization failed");
		return false;
	}

	// configure Arduino LED pin for output
	pinMode(LED_PIN, OUTPUT);

	return true;
}

void Device::Update() {
	logTrace("Device::Update start");

	// Обновление состояния пальца
	pFinger->Update();
	// Обновлене состояния BLE
	std::string str = pBluetooth->GetCharacteristicValue("servo");
	if (str == "1") {
		this->pFinger->Expand();
	} else if (str == "2") {
		this->pFinger->Bend();
	}
	// Обновление состояния акселерометра
	pAccelerometer->Update();

	// Мигания светодиодом для обозначения активности
	blinkState = !blinkState;
	digitalWrite(LED_PIN, static_cast<uint8_t>(blinkState));
}
