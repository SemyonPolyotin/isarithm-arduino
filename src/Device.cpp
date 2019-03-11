#include <Device.h>

#include <esp32-hal.h>

#include <utils/Log.h>

#define LED_PIN 2
bool blinkState = false;

// Последняя переданная команда BLE
FingerCommand servoCommand = FC_UNDEFINED;

// Данные акселерометра прошлой итерации
AccelerometerData lastAccelerometerData = Accelerometer::GetDefaultData();

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
	std::string servoCommandStr = pBluetooth->GetCharacteristicValue("servo");

	// Обновление состояния акселерометра
	pAccelerometer->Update();

	AccelerometerData newAccelerometerData = pAccelerometer->GetData();

	// Обработка входящих команд
	if (servoCommandStr == "bend") {
		servoCommand = FC_BEND;
	} else if (servoCommandStr == "expand") {
		servoCommand = FC_EXPAND;
	} else if (servoCommandStr == "default") {
		servoCommand = FC_DEFAULT;
	}

	// Обработка данных акселерометра
	if (!(lastAccelerometerData.ax == 0 && lastAccelerometerData.ay == 0)) {
		if (abs(newAccelerometerData.ax - lastAccelerometerData.ax) > 3000) {
			servoCommand = FC_EXPAND;
		}
	}
	lastAccelerometerData = newAccelerometerData;

	//  Принятие решений по управлению пальцем
	switch (servoCommand) {
		case FC_BEND:
			pFinger->Bend();
			break;
		case FC_DEFAULT:
			pFinger->Default();
			break;
		case FC_EXPAND:
			pFinger->Expand();
			break;
		case FC_UNDEFINED:
		default:
			break;
	}
	servoCommand = FC_UNDEFINED;

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
