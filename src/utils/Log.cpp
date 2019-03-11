#include <utils/Log.h>

#include <HardwareSerial.h>

bool logInit() {
	Serial.begin(9600);
	logInfo("Log initialized");
	return true;
}

void logWriteLn(std::string buf) {
//	Serial.println(buf.c_str());
}

void LogWriteBreak() {
	logWriteLn("==============================================================");
}

void logTrace(std::string buf) {
	logWriteLn(std::move(buf));
}

void logDebug(std::string buf) {
	logWriteLn(std::move(buf));
}

void logInfo(std::string buf) {
	logWriteLn(std::move(buf));
}

void logWarning(std::string buf) {
	logWriteLn(std::move(buf));
}

void logError(std::string buf) {
	logWriteLn(std::move(buf));
}
