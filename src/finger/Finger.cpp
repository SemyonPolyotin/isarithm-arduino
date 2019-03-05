#include <finger/Finger.h>

#include <utils/Log.h>

Finger::Finger() {
	logTrace("Finger::Finger start");
	// Создание и инициализация первого серво двигателя
	pDrive = new Drive(13, "one");
}

bool Finger::Init() {
	logTrace("Finger::Init start");
	if (!pDrive->Init(Drive::defaultAngle)) {
		logWriteLn("Drive one initialization failed");
	}
	return true;
}

void Finger::Update() {
	logTrace("Finger::Update start");
	// Обновление состояния серво двигателя
	pDrive->Update();
}

void Finger::Reset() {
	logTrace("Finger::Reset start");
	pDrive->ChangeAngle(90, 0);
}

void Finger::Expand() {
	logTrace("Finger::Expand start");
	// Разгибание пальца
	pDrive->MoveDirection(DriveMoveSpeed::MEDIUM, 1);
}

void Finger::Bend() {
	logTrace("Finger::Bend start");
	// Сгибание пальца
	pDrive->MoveDirection(DriveMoveSpeed::MEDIUM, -1);
}
