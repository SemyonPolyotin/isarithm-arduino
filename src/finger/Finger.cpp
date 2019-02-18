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

bool Finger::Init() {
	logTrace("Finger::Init start");
	logTrace("Finger::Init end");
	return true;
}

void Finger::Update() {
	logTrace("Finger::update start");
	// Обновление состояния серво двигателя
	pDrive->update();
	logTrace("Finger::update end");
}

void Finger::Reset() {
	logTrace("Finger::Reset start");
	pDrive->ChangeAngle(90, 0);
	logTrace("Finger::Reset end");
}

void Finger::Expand() {
	logTrace("Finger::Expand start");
	// Разгибание пальца
	pDrive->MoveDirection(DriveMoveSpeed::MEDIUM, 1);
	logTrace("Finger::Expand end");
}

void Finger::Bend() {
	logTrace("Finger::Bend start");
	// Сгибание пальца
	pDrive->MoveDirection(DriveMoveSpeed::MEDIUM, -1);
	logTrace("Finger::Bend end");
}
