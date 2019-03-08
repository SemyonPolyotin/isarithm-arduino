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

	/**
	 * Перемещение пальца в позицию разворота
	 */
	void Expand();

	/**
	 * Перемещение пальца в позицию сгиба
	 */
	void Bend();

	/**
	 * Перемещение пальца в позицию по умолчанию
	 */
	void Default();

private:
	// Сервопривод
	Drive* pDrive;

};
