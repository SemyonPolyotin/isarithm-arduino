#pragma once

#include <iostream>

/**
 * Инициализация логирвоания
 * @return
 */
bool logInit();

/**
 * Печать строки
 * @param buf Входная строка
 */
void logWriteLn(std::string buf);

/**
 * Вывод отслеживающей информации
 * @param buf Входная строка
 */
void logTrace(std::string buf);

/**
 * Вывод отладочной информации
 * @param buf Входная строка
 */
void logDebug(std::string buf);

/**
 * Вывод информационной информации
 * @param buf Входная строка
 */
void logInfo(std::string buf);

/**
 * Вывод предупреждающей информации
 * @param buf Входная строка
 */
void logWarning(std::string buf);

/**
 * Вывод ошибочной информации
 * @param buf Входная строка
 */
void logError(std::string buf);

/**
 * Вывести разделеине
 */
void LogWriteBreak();
