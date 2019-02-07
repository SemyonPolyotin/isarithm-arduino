#include <Device.h>

#include <utils/Log.h>

Device::Device(std::string name) {
	logDebug("Device::Device start");
	this->name = name;
	logInfo("Initializing device " + name);
	delay(2000);
	logDebug("Device::Device end");
}

bool Device::init() {
	logDebug("Device::Init start");
	// Ининциализация пальца
	pFinger = new Finger();
	if (!pFinger->Init()) {
		logError("Finger initialization failed");
		return false;
	}
	// Инициализация Bluetooth
	pBluetooth = new Bluetooth();
	logDebug("Device::Init end");
	return true;
}

void Device::update() {
	logDebug("Device::update start");
	// Обновление состояния пальца
	pFinger->Update();

	std::string str = pBluetooth->GetCharacteristicValue("servo");
	if (str == "1") {
		this->pFinger->Expand();
	} else if (str == "2") {
		this->pFinger->Bend();
	}

	logDebug("Device::update end");
}
