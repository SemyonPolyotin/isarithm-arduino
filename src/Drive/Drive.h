#pragma once

#include <ESP32Servo.h> 

enum DriveState
{
    UNDEFINED = 0,

    ANGLE,  // Смена угла
    MOVE,   // Движение в направлении
};

enum DriveMoveSpeed
{
    SLOW = 0,   // Медлено
    MEDIUM = 1, // Средне
    FAST = 2,   // Быстро
};

// Класс для управления серво двигателем
class Drive
{
private:
    // Серво двигатель
    Servo servo;

    // Текущее состояние двигателя
    DriveState state = UNDEFINED;
    // Текущий угол повопрота
    int currentAngle;

    // Целевое направление смены угла
    int angleTo;
    // Напрвление движения
    int moveDir = 0;

public:
    Drive(int pin);
    ~Drive();

    // Получить текущий угол
    int GetAngle()
    {
        return currentAngle;
    }

    // Получить состояние двигатаеля
    DriveState GetState()
    {
        return state;
    }

    // Установить угол (мгновенно)
    void SetAngle(unsigned int angle);
    // Установить угол (за время)
    void SetAngleSlow(int angle, unsigned int time);
    // Поворачивать в заданном направлении со скоростью
    void Move(DriveMoveSpeed speed, bool direction);

};
