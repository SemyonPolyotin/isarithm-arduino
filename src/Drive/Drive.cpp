#include "Drive.h"

const int STEP_SIZE = 10;

Drive::Drive(int pin)
{
    // Стандартная частота работы серво двигаетля
    servo.setPeriodHertz(50);
    // Подключение к сервоприводу с данными значениями задержек
    servo.attach(pin, 500, 2400);
}

Drive::~Drive()
{
}

void Drive::SetAngle(unsigned int angle)
{
    servo.write(angle);
    currentAngle = angle;
}

// TODO: Перейти на state режим
void Drive::SetAngleSlow(int angle, unsigned int time)
{
    if (angle > 180) angle = 180;
    if (currentAngle == angle) return;

    int dir = (angle - currentAngle) / abs(angle - currentAngle);

    unsigned int numSteps = abs(angle - currentAngle) / STEP_SIZE;

    for (unsigned int step = 0; step <= numSteps; step++)
    {
        delay(time / numSteps);
        myservo.write(currentAngle + dir * step * (STEP_SIZE));
    }
    currentAngle = angle;
    myservo.write(currentAngle);
}

void Drive::Move(DriveMoveSpeed speed, bool direction)
{
    // TODO: Реализовать в дальнейшем
}
