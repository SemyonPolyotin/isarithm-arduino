#include <Arduino.h>

#include <utils/Log.h>
#include <Device.h>

// Глобальная переменная устройства
Device* g_pDevice;

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

	logWriteLn("Program started");
}

// Основной цикл программы
void loop() {
	// Обновление устройтва
	g_pDevice->update();

	LogWriteBreak();
}
