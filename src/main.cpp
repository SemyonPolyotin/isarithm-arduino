#include <Arduino.h>
#include <ESP32Servo.h> 

#include "Drive/Drive.h"

Drive* drive;

// Настройка программы
void setup()
{
	// Создание и инициализация первого серво двигателя
	drive = new Drive(18);
	drive->SetAngle(0);
}

// Основной цикл программы
void loop()
{
	// Обновление состояния серво двигателя
	drive->SetAngleSlow(180, 1000);
	delay(1000);
	drive->SetAngleSlow(0, 1000);
	delay(1000);
}
