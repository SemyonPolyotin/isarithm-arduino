#include <activity/ActivityStorage.h>

#include <utils/Log.h>

#include <EEPROM.h>

// Изменить это значение при обновлении данных и сброса
#define DATA_VALID 180

ActivityStorage::ActivityStorage() {
	logTrace("ActivityStorage::ActivityStorage start");
}

bool ActivityStorage::Init() {
	logTrace("ActivityStorage::Init start");
	this->Get();
	if (this->data.dataValid != DATA_VALID) {
		this->Create();
	}
	return false;
}

ActivityData ActivityStorage::Get() {
	logTrace("ActivityStorage::Get start");
	EEPROM.begin(sizeof(this->data));
	EEPROM.get(0, this->data);
	return this->data;
}

bool ActivityStorage::Save() {
	logTrace("ActivityStorage::Save start");
	EEPROM.put(0, this->data);
	EEPROM.commit();

	return true;
}

bool ActivityStorage::Create() {
	logTrace("ActivityStorage::Create start");
	this->data.dataValid = DATA_VALID;

	return this->Save();
}
