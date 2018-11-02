#include <Arduino.h>
#include <ESP32Servo.h> 

#include "Drive/Drive.h"

// #define F_CPU 8000000 // Частота контроллера

Drive* drive1;
Drive* drive2;

// Настройка программы
void setup()
{
	Serial.begin(9600);

	// Создание и инициализация первого серво двигателя
	drive1 = new Drive(18, "one");
	if (!drive1->Init(90))
	{
		// TODO: Выйти из программы
	}
	delay(2000);
	Serial.println("Program started");
}

enum SimType
{
	ST_SWITCH,
	ST_MOVE,
};

bool up = true;
int switchTime = 5000;

void Simulate(SimType simType)
{
	int time = millis();
	switch (simType)
	{
		// Симуляция управления (смена от 0 до 180 за switchTime, пауза)
		case SimType::ST_SWITCH:
			if (0 < time % (2 * switchTime) && time % (2 * switchTime) < switchTime && up)
			{
				Serial.println("Change to 180");
				drive1->ChangeAngle(180, switchTime / 2);
				up = !up;
			}
			else if (switchTime < time % (2 * switchTime) && time % (2 * switchTime) < 2 * switchTime && !up)
			{
				Serial.println("Ghange to 0");
				drive1->ChangeAngle(0, switchTime / 2);
				up = !up;
			}
			break;

		// Движение в заданном направлении
		case SimType::ST_MOVE:
			if (0 < time % (2 * switchTime) && time % (2 * switchTime) < switchTime && up)
			{
				Serial.println("Move towards positive");
				drive1->MoveDirection(DriveMoveSpeed::MEDIUM, +1);
				up = !up;
			}
			else if (switchTime < time % (2 * switchTime) && time % (2 * switchTime) < 2 * switchTime && !up)
			{
				Serial.println("Move towards negative");
				drive1->MoveDirection(DriveMoveSpeed::MEDIUM, -1);
				up = !up;
			}
			break;

		default:
			break;
	}
	
}

SimType simType = SimType::ST_MOVE;

// Основной цикл программы
void loop()
{
	// Обновление подсистем
	drive1->Update();		// Обновление состояния серво двигателя

	Simulate(simType);		// Симуляция управляющих воздействий

	// delay(switchTime / 20);
	Serial.println("==============================================================");
}
