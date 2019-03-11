#include <drive/Drive.h>

#include <utils/Log.h>

int StraightenAngle(int angle) {
	if (angle > Drive::maxAngle) angle = Drive::maxAngle;
	if (angle < Drive::minAngle) angle = Drive::minAngle;
	return angle;
}

Drive::Drive(int pin, std::string name) {
	logTrace("Drive::Drive start");
	// Стандартная частота работы серво двигаетля
	servo.setPeriodHertz(50);
	// Подключение к сервоприводу с данными значениями задержек
	servo.attach(pin, 500, 2400);
	this->name = std::move(name);
	logTrace("Drive::Drive end");
}

bool Drive::Init(int initialAngle) {
	logTrace("Drive::Init start");
	logInfo("Drive " + name + ": Initializing servo Drive");

	// Установить состояние ожидания
	state = DriveState::WAITING;
	// Перейти в начальное положение
	SetAngle(initialAngle);

	logTrace("Drive::Init end");
	return true;
}

Drive::~Drive()
= default;

void Drive::SetAngle(int newAngle) {
	logTrace("Drive::SetAnge start");
	logInfo("Drive " + name + ": SetAngle()");

	newAngle = StraightenAngle(newAngle);

	logInfo("newAngle = " + std::string(String(newAngle).c_str()));

	if (currentAngle == newAngle) return;

	servo.write(newAngle);
	currentAngle = newAngle;
	logTrace("Drive::SetAnge end");
}

void Drive::Update() {
	logTrace("");
	logInfo("Drive " + name + ": Update()");
	logInfo("currentAngle = " + std::string(String(currentAngle).c_str()));

	int newAngle = currentAngle;
	unsigned long time = millis();                // Текущее время
	unsigned long timeDiff = time - lastUpdate;    // Прошедшее время
	logInfo("timeDiff = " + std::string(String(timeDiff).c_str()));
	switch (state) {
		case DriveState::CHANGE_ANGLE:
			// Смена угла в течении времени
			newAngle = static_cast<int>(currentAngle + changeAngleSpeed * (float) timeDiff);
			logInfo("newAngle = " + std::string(String(newAngle).c_str()));
			if ((newAngle > changeAngleTo && changeAngleDir == 1) ||
				(newAngle < changeAngleTo && changeAngleDir == -1)) {
				newAngle = changeAngleTo;
				state = DriveState::WAITING;
			}
			break;

		case DriveState::MOVE_DIRECTION:
			// Двидение в направлении со скоростью
			newAngle = static_cast<int>(currentAngle + moveDirectionDir * koef * moveDirectionSpeed * timeDiff);
			logInfo("newAngle = " + std::string(String(newAngle).c_str()));
			if (newAngle > 180) {
				newAngle = 180;
				state = DriveState::WAITING;
			} else if (newAngle < Drive::minAngle) {
				newAngle = Drive::minAngle;
				state = DriveState::WAITING;
			}
			break;

		case DriveState::WAITING:
		case DriveState::DS_UNDEFINED:
		default:
			break;
	}

	if (currentAngle != newAngle) {
		SetAngle(newAngle);
	}
	// Обновление
	lastUpdate = time;
}

void Drive::ChangeAngle(int newAngle, int time) {
	logTrace("Drive " + name + ": ChangeAngle()");

	newAngle = StraightenAngle(newAngle);

	// Если угл не изменился
	if (currentAngle == newAngle) return;

	logInfo("newAngle = " + std::string(String(newAngle).c_str()));

	state = DriveState::CHANGE_ANGLE;
	changeAngleDir = (newAngle - currentAngle) / abs(newAngle - currentAngle);
	changeAngleTo = newAngle;
	changeAngleSpeed = ((float) newAngle - (float) currentAngle) / (float) time;
	changeAngleTime = time;

	logInfo("state = " + std::string(String(state).c_str()));
	logInfo("changeAngleDir = " + std::string(String(changeAngleDir).c_str()));
	logInfo("changeAngleTo = " + std::string(String(changeAngleTo).c_str()));
	logInfo("changeAngleSpeed = " + std::string(String(changeAngleSpeed).c_str()));
	logInfo("changeAngleTime = " + std::string(String(changeAngleTime).c_str()));
}

void Drive::MoveDirection(DriveMoveSpeed speed, int direction) {
	logTrace("Drive " + name + ": MoveDirection()");

	logInfo(std::string(String(direction).c_str()));

	if (direction > 0) direction = 1;
	if (direction < 0) direction = -1;
	if (direction == 0) return;
	if (currentAngle == 180 && direction == +1) return;
	if (currentAngle == 0 && direction == -1) return;

	state = DriveState::MOVE_DIRECTION;
	moveDirectionSpeed = speed;
	moveDirectionDir = direction;

	logInfo("state = " + std::string(String(state).c_str()));
	logInfo("moveDirectionSpeed = " + std::string(String(moveDirectionSpeed).c_str()));
	logInfo("moveDirectionDir = " + std::string(String(moveDirectionDir).c_str()));
}
