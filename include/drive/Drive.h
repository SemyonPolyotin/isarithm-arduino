#pragma once

#include <ESP32Servo.h>
#include <string>

enum DriveState
{
	UNDEFINED = 0,

	// Ожидание
	WATING,
	// Смена угла
	CHANGE_ANGLE,
	// Движение в направлении
	MOVE_DIRECTION,
};

enum DriveMoveSpeed
{
	DMS_UNDEFINED = 0,
	SLOW = 1,		// Медлено
	MEDIUM = 2,		// Средне
	FAST = 3,		// Быстро
};

// Класс для управления серво двигателем
class Drive
{
private:
	// Имя двигателя
	std::string name = "name_undefined";

	// Серво двигатель
	Servo servo;

	// Текущее состояние двигателя
	DriveState state = DriveState::UNDEFINED;
	// Текущий угол повопрота
	int currentAngle;

	// Время последнего обновления
	unsigned long lastUpdate = 0;

	// Целевое направление смены угла
	int changeAngleTo;
	// Направление смены угла
	int changeAngleDir = 0;
	// Время смены угла
	int changeAngleTime;
	// Скорость смены угла
	float changeAngleSpeed = 0.0f;

	// Напрвление движения в сторону
	int moveDirectionDir = 0;
	// Скорость движения в сторону
	DriveMoveSpeed moveDirectionSpeed = DriveMoveSpeed::DMS_UNDEFINED;
	// Коэфициент скорости движения
	float koef = 0.02f;

	// Установить угол (мгновенно)
	void SetAngle(int angle);

public:
	Drive(int pin, std::string name);
	~Drive();

	bool init(int initialAngle);

	// Обновить состояние двигателя
	void update();

	// Получить текущий угол
	inline int GetAngle()
	{
		return currentAngle;
	}

	// Получить состояние двигатаеля
	inline DriveState GetState()
	{
		return state;
	}
	// Установить угол (за время)
	void ChangeAngle(int angle, int time);

	// Поворачивать в заданном направлении со скоростью
	void MoveDirection(DriveMoveSpeed speed, int direction);

};

int StraightenAngle(int angle);