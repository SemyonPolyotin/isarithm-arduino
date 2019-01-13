#include <utils/Log.h>

#include <HardwareSerial.h>

int LogInit() {
	Serial.begin(9600);
}

void LogWriteLn(std::string buf) {
	Serial.println(buf.c_str());
}
