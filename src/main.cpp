#include <Arduino.h>

#include <utils/Log.h>
#include <Device.h>
#include <bluetooth/Bluetooth.h>

// Глобальная переменная устройства
Device* g_pDevice;

Drive* drive1;
Drive* drive2;

// Настройка программы
void setup() {
	// Инициализация логирования
	logInit();

	// Ининциализация устройства
	g_pDevice = new Device("Isarithm");
	if (!g_pDevice->init()) {
		// Перезапуск контроллера
		logError("Device initialization failed");
		digitalWrite(3, LOW);
	};

bool up = true;
int switchTime = 5000;

void Simulate(SimType simType)
{
	unsigned long time = millis();
	switch (simType)
	{
		// Симуляция управления (смена от 0 до 180 за switchTime, пауза)
		case SimType::ST_SWITCH:
			if (0 < time % (2 * switchTime) && time % (2 * switchTime) < switchTime && up)
			{
				LogWriteLn("Change to 180");
				drive1->ChangeAngle(180, switchTime / 2);
				up = !up;
			}
			else if (switchTime < time % (2 * switchTime) && time % (2 * switchTime) < 2 * switchTime && !up)
			{
				LogWriteLn("Ghange to 0");
				drive1->ChangeAngle(0, switchTime / 2);
				up = !up;
			}
			break;

		// Движение в заданном направлении
		case SimType::ST_MOVE:
			if (0 < time % (2 * switchTime) && time % (2 * switchTime) < switchTime && up)
			{
				LogWriteLn("Move towards positive");
				drive1->MoveDirection(DriveMoveSpeed::MEDIUM, +1);
				up = !up;
			}
			else if (switchTime < time % (2 * switchTime) && time % (2 * switchTime) < 2 * switchTime && !up)
			{
				LogWriteLn("Move towards negative");
				drive1->MoveDirection(DriveMoveSpeed::MEDIUM, -1);
				up = !up;
			}
			break;

	logWriteLn("Program started");
}

// Основной цикл программы
void loop() {
	// Обновление устройтва
	g_pDevice->update();

	LogWriteBreak();
}
