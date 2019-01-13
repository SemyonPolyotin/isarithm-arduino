#pragma once

#include <drive/Drive.h>

/**
 * Класс описания пальца
 */
class Finger {
public:
	Finger();
	/**
	 * Инициализация пальца
	 */
	bool init();
	/**
	 * Обновление состояния пальца
	 */
	void update();

private:
	// Сервопривод
	Drive* pDrive;

};
