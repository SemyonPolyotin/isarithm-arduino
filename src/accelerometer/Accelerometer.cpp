#include <accelerometer/Accelerometer.h>

#include <utils/Log.h>

#include <Wire.h>
#include <HardwareSerial.h>

Accelerometer::Accelerometer() {
	logTrace("Accelerometer::Accelerometer start");

	// Инициализация I2C линии
	Wire.begin();

	// Инициализация I2C устройства
	logInfo("Initializing I2C devices...");
	mpu.initialize();
}

bool Accelerometer::Init() {
	logTrace("Accelerometer::Init start");

	// Проверка соединения
	logInfo("Testing device connections...");
	if (!mpu.testConnection()) {
		logError("MPU6050 connection failed");
		return false;
	}

	logInfo("MPU6050 connection successful");
	return true;
}

void Accelerometer::Update() {
	logTrace("Accelerometer::Update start");

	mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

	Serial.println(ax);
	Serial.println(ay);
	Serial.println(az);
	Serial.println(gx);
	Serial.println(gy);
	Serial.println(gz);
}
