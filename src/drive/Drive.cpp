#include <drive/Drive.h>

#include <utility>
#include <string>

#include <WString.h>
#include <esp32-hal.h>
#include <HardwareSerial.h>

#include <utils/Log.h>

int StraightenAngle(int angle)
{
	if (angle > 180) angle = 180;
	if (angle < 0) angle = 0;
	return angle;
}

Drive::Drive(int pin, std::string name)
{
	logTrace("Drive::Drive start");
	// Стандартная частота работы серво двигаетля
	servo.setPeriodHertz(50);
	// Подключение к сервоприводу с данными значениями задержек
	servo.attach(pin, 500, 2400);
	this->name = std::move(name);
	logTrace("Drive::Drive end");
}

bool Drive::init(int initialAngle)
{
	logTrace("Drive::Init start");
	logInfo("Drive "+ name +": Initializing serial Drive");

	// Установить состояние ожидания
	state = DriveState::WATING;
	// Перейти в начальное положение
	SetAngle(initialAngle);

	logTrace("Drive::Init end");
	return true;
}

Drive::~Drive()
= default;

void Drive::SetAngle(int newAngle)
{
	logTrace("Drive::SetAnge start");
	logInfo("Drive "+ name +": SetAngle()");

	newAngle = StraightenAngle(newAngle);

	Serial.println("newAngle = " + String(newAngle));

	if (currentAngle == newAngle) return;

	servo.write(newAngle);
	currentAngle = newAngle;
	logTrace("Drive::SetAnge end");
}

void Drive::update()
{
	logTrace("");
	logInfo("Drive "+ name + ": Update()");
	logInfo("currentAngle = " + std::string(String(currentAngle).c_str()));

	int newAngle = currentAngle;
	unsigned long time = millis();				// Текущее время
	unsigned long timeDiff = time - lastUpdate;	// Прошедшее время
	Serial.println("timeDiff = " + String(timeDiff));
	switch (state)
	{
		// Смена угла в течении времени
		case DriveState::CHANGE_ANGLE:
			newAngle = static_cast<int>(currentAngle + changeAngleSpeed * (float) timeDiff);
			Serial.println("newAngle = " + String(newAngle));
			if ((newAngle > changeAngleTo && changeAngleDir == 1) || (newAngle < changeAngleTo && changeAngleDir == -1))
			{
				newAngle = changeAngleTo;
				state = DriveState::WATING;
			}
			break;

		// Двидение в направлении со скоростью
		case DriveState::MOVE_DIRECTION:
			newAngle = static_cast<int>(currentAngle + moveDirectionDir * koef * moveDirectionSpeed * timeDiff);
			Serial.println("newAngle = " + String(newAngle));
			if (newAngle > 180)
			{
				newAngle = 180;
				state = DriveState::WATING;
			}
			else if (newAngle < 0)
			{
				newAngle = 0;
				state = DriveState::WATING;
			}
			break;

		case DriveState::WATING:
		case DriveState::UNDEFINED:
		default:
			break;
	}

	if (currentAngle != newAngle)
	{
		SetAngle(newAngle);
	}
	// Обновление
	lastUpdate = time;
}

void Drive::ChangeAngle(int newAngle, int time)
{
	logTrace("Drive "+ name + ": ChangeAngle()");

	newAngle = StraightenAngle(newAngle);

	// Если угл не изменился
	if (currentAngle == newAngle) return;

	Serial.println("newAngle = " + String(newAngle));

	state = DriveState::CHANGE_ANGLE;
	changeAngleDir = (newAngle - currentAngle) / abs(newAngle - currentAngle);
	changeAngleTo = newAngle;
	changeAngleSpeed = ((float) newAngle - (float) currentAngle) / (float) time;
	changeAngleTime = time;

	Serial.println("state = " + String(state));
	Serial.println("changeAngleDir = " + String(changeAngleDir));
	Serial.println("changeAngleTo = " + String(changeAngleTo));
	Serial.println("changeAgleSpeed = " + String(changeAngleSpeed));
	Serial.println("changeAngleTime = " + String(changeAngleTime));
}

void Drive::MoveDirection(DriveMoveSpeed speed, int direction)
{
	logTrace("Drive "+ name + ": MoveDirection()");

	Serial.println(direction);

	if (direction > 0) direction = 1;
	if (direction < 0) direction = -1;
	if (direction == 0) return;
	if (currentAngle == 180 && direction == +1) return;
	if (currentAngle == 0 && direction == -1) return;

	state = DriveState::MOVE_DIRECTION;
	moveDirectionSpeed = speed;
	moveDirectionDir = direction;

	Serial.println("state = " + String(state));
	Serial.println("moveDirectionSpeed = " + String(moveDirectionSpeed));
	Serial.println("moveDirectionDir = " + String(moveDirectionDir));
}
