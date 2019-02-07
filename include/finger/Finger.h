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
	bool Init();
	/**
	 * Обновление состояния пальца
	 */
	void Update();

	void Reset();

	void Expand();

	void Bend();

private:
	// Сервопривод
	Drive* pDrive;

};
