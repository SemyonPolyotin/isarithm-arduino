#include <accelerometer/Accelerometer.h>

#include <utils/Log.h>

#include <Wire.h>
#include <HardwareSerial.h>

#define LED_PIN 2
bool blinkState = false;

Accelerometer::Accelerometer() {
	logTrace("Accelerometer::Accelerometer start");

	Wire.begin();

	// initialize device
	Serial.println("Initializing I2C devices...");
	accelgyro.initialize();

	// verify connection
	logInfo("Testing device connections...");
	accelgyro.testConnection() ? logInfo("MPU6050 connection successful") : logError("MPU6050 connection failed");

	// configure Arduino LED pin for output
	pinMode(LED_PIN, OUTPUT);
}

void Accelerometer::update() {
	logTrace("Accelerometer::Accelerometer start");

	accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

	Serial.println(ax);
	Serial.println(ay);
	Serial.println(az);
	Serial.println(gx);
	Serial.println(gy);
	Serial.println(gz);

	// blink LED to indicate activity
	blinkState = !blinkState;
	digitalWrite(LED_PIN, static_cast<uint8_t>(blinkState));
}
