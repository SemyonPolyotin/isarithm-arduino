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
	logDebug("Device::init start");
	// Ининциализация пальца
	pFinger = new Finger();
	if (!pFinger->init()) {
		logError("Finger initialization failed");
		return false;
	}
	// Инициализация Bluetooth
	pBluetooth = new Bluetooth();
	logDebug("Device::init end");
	return true;
}

void Device::update() {
	logDebug("Device::update start");
	// Обновление состояния пальца
	pFinger->update();
	logDebug("Device::update end");
}
