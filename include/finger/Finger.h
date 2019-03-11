#pragma once

#include <drive/Drive.h>

enum FingerCommand {
	FC_UNDEFINED = 0,
	FC_BEND = 1,
	FC_DEFAULT = 2,
	FC_EXPAND = 3
};

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
