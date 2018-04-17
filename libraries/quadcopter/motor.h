#ifndef MOTOR_H
#define MOTOR_H

#include <Servo.h>

class Motor final
{
public:
    explicit Motor(int pwmPin);
    ~Motor();

    void init();

    int cutOverLimits(int rawThrottle);
    void write(int inpThrottle);


private:
    Servo m_servo;

    int m_pwmPin;
    int m_lastThrottleVal;

    static const int MIN = 1000;
    static const int MAX = 2000;
};

#endif
