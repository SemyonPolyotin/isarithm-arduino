#pragma once

/**
 * Структура хранения временных записей
 */
struct TimeRecord {
	int accelerationX;
	int accelerationY;
	int accelerationZ;
};

#define MAX_NUM_RECORDS 10

/**
 * Структура хранения активностей
 */
struct Activity {
	unsigned int id;
	unsigned int tolerance;
	unsigned int numTimeRecords;
	TimeRecord timeRecords[MAX_NUM_RECORDS];
};

#define MAX_NUM_ACTIVITIES 2

/**
 * Данные активностей
 */
struct ActivityData {
	Activity activities[MAX_NUM_ACTIVITIES];
	unsigned int dataValid;
};

/**
 * Класс доступа к активностям в памяти устройства
 */
class ActivityStorage {
public:
	ActivityStorage();

	/**
	 * Инизациализация хранения активностей
	 * @return Результат инициализации
	 */
	bool Init();

	/**
	 * Получение активностей из памяти
	 */
	ActivityData Get();

	/**
	 * Записать
	 * @return Результат записи
	 */
	bool Save();

protected:
	/**
	 * Создать первичную запись данных в EEPROM
	 * @return Резултат записи
	 */
	bool Create();

private:
	// Данные в памяти
	ActivityData data;

};