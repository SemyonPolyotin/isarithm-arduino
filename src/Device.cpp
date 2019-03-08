#include <Device.h>

#include <esp32-hal.h>

#include <utils/Log.h>

#define LED_PIN 2
bool blinkState = false;

std::string lastKnownCommand = "default";

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

	// Конфигурации LED для индикации состояния
	pinMode(LED_PIN, OUTPUT);

	return true;
}

void Device::Update() {
	logTrace("Device::Update start");

	// Обновлене состояния BLE
	std::string servoCommand = pBluetooth->GetCharacteristicValue("servo");

	// Обновление состояния акселерометра
	pAccelerometer->Update();

	// Принятие решений по управлению пальцем
	if (lastKnownCommand != servoCommand) {
		if (servoCommand == "bend") {
			this->pFinger->Bend();
		} else if (servoCommand == "expand") {
			this->pFinger->Expand();
		} else if (servoCommand == "default") {
			this->pFinger->Default();
		}
		lastKnownCommand = servoCommand;
	}

	// Обновление состояния пальца
	pFinger->Update();

	// Мигания светодиодом для обозначения активности
	if (pBluetooth->IsConnected()) {
		digitalWrite(LED_PIN, 1);
	} else {
		blinkState = !blinkState;
		digitalWrite(LED_PIN, static_cast<uint8_t>(blinkState));
	}
}
