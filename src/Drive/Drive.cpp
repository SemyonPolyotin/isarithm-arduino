#include "Drive.h"

int StraightenAnlge(int angle)
{
	if (angle > 180) angle = 180;
	if (angle < 0) angle = 0;
	return angle;
}

String output;

Drive::Drive(int d_pin, String d_name)
{
	// Стандартная частота работы серво двигаетля
	servo.setPeriodHertz(50);
	// Подключение к сервоприводу с данными значениями задержек
	servo.attach(d_pin, 500, 2400);
	name = d_name;
}

bool Drive::Init(int initialAngle)
{
	Serial.println("Drive "+ name +": Initializing serial drive");

	// Установить состояние ожидания
	state = DriveState::WATING;
	// Перейти в начальное положение
	SetAngle(initialAngle);

	return true;
}

Drive::~Drive()
{
}

void Drive::SetAngle(int newAngle)
{
	Serial.println("Drive "+ name +": SetAngle()");

	newAngle = StraightenAnlge(newAngle);

	Serial.println("newAngle = " + String(newAngle));

	if (currentAngle == newAngle) return;

	servo.write(newAngle);
	currentAngle = newAngle;
}

void Drive::Update()
{
	Serial.println("Drive "+ name + ": Update()");
	Serial.println("currentAngle = " + String(currentAngle));

	int newAngle = currentAngle;
	int time = millis();				// Текущее время
	int timeDiff = time - lastUpdate;	// Прошедшее время
	Serial.println("timeDiff = " + String(timeDiff));
	switch (state)
	{
		// Смена угла в течении времени
		case DriveState::CHANGE_ANGLE:
			newAngle = currentAngle + changeAngleSpeed * (float) timeDiff;
			Serial.println("newAngle = " + String(newAngle));
			if ((newAngle > changeAngleTo && changeAngleDir == 1) || (newAngle < changeAngleTo && changeAngleDir == -1))
			{
				newAngle = changeAngleTo;
				state = DriveState::WATING;
			}
			break;

		// Двидение в направлении со скоростью
		case DriveState::MOVE_DIRECTION:
			newAngle = currentAngle + (int) moveDirectionDir * koef * moveDirectionSpeed * timeDiff;
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
	lastUpdate = time;	// Обновление 
}

void Drive::ChangeAngle(int newAngle, int time)
{
	Serial.println("Drive "+ name + ": ChangeAngle()");

	newAngle = StraightenAnlge(newAngle);

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

// TODO: Реализовать в дальнейшем
void Drive::MoveDirection(DriveMoveSpeed speed, int direction)
{
	Serial.println("Drive "+ name + ": MoveDirection()");

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
