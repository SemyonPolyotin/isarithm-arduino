#include <Arduino.h>
#include <ESP32Servo.h> 

#include "Drive/Drive.h"

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

bool up = true;
int switchTime = 5000;

// Основной цикл программы
void loop()
{
	// Обновление подсистем
	drive1->Update();		// Обновление состояния серво двигателя

	// Симуляция управления (смена от 0 до 180 за 2, пауза 3 сек)
	int time = millis();
	if (0 < time % (2 * switchTime) && time % (2 * switchTime) < switchTime && up)
	{
		Serial.println("Moving towards 180");
		drive1->ChangeAngle(180, switchTime / 2);
		up = !up;
	}
	else if (switchTime < time % (2 * switchTime) && time % (2 * switchTime) < 2 * switchTime && !up)
	{
		Serial.println("Moving towards 0");
		drive1->ChangeAngle(0, switchTime / 2);
		up = !up;
	}
	
	delay(switchTime/10);
}
