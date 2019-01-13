#include <finger/Finger.h>

#include <utils/Log.h>

Finger::Finger() {
	logTrace("Finger::Finger start");
	// Создание и инициализация первого серво двигателя
	pDrive = new Drive(18, "one");
	if (!pDrive->init(90)) {
		logWriteLn("Drive one initialization failed");
	}
	logTrace("Finger::Finger end");
}

bool Finger::init() {
	logTrace("Finger::init start");
	logTrace("Finger::init end");
	return true;
}

void Finger::update() {
	logTrace("Finger::update start");
	// Обновление состояния серво двигателя
	pDrive->update();
	logTrace("Finger::update end");
}
