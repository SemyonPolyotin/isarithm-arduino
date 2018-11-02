#pragma once

#include <ESP32Servo.h>

enum DriveState
{
	UNDEFINED = 0,

	// Смена угла
	CHANGE_ANGLE,
	// Движение в направлении
	MOVE_DIRECTION,
};

enum DriveMoveSpeed
{
	SLOW = 0,   // Медлено
	MEDIUM = 1, // Средне
	FAST = 2,   // Быстро
};

// Класс для управления серво двигателем
class Drive
{
private:
	// Имя двигателя
	String name = "no_name";

	// Серво двигатель
	Servo servo;

	// Текущее состояние двигателя
	DriveState state = DriveState::UNDEFINED;
	// Текущий угол повопрота
	int currentAngle;

	// Время последнего обновления
	int lastUpdate = 0;

	// Целевое направление смены угла
	int changeAngleTo;
	// Направление смены угла
	int changeAngleDir = 0;
	// Время смены угла
	int changeAngleTime;
	// Скорость смены угла
	float changeAngleSpeed = 0.0f;

	// Напрвление движения
	int moveDir = 0;

	// Установить угол (мгновенно)
	void SetAngle(int angle);

public:
	Drive(int pin, String name);
	~Drive();

	bool Init(int initialAngle);

	// Обновить состояние двигателя
	void Update();

	// Получить текущий угол
	int GetAngle()
	{
		return currentAngle;
	}

	// Получить состояние двигатаеля
	DriveState GetState()
	{
		return state;
	}
	// Установить угол (за время)
	void ChangeAngle(int angle, int time);

	// Поворачивать в заданном направлении со скоростью
	void MoveDirection(DriveMoveSpeed speed, bool direction);

};

int StraightenAnlge(int angle);