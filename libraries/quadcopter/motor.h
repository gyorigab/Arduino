#ifndef MOTOR_H
#define MOTOR_H

#include <Servo.h>

class Motor final
{
public:
    explicit Motor(uint8_t pwmPin);
    ~Motor();

    void init();

    int cutOverLimits(int16_t rawThrottle);
    void write(int16_t inpThrottle);


private:
    Servo m_servo;

    uint8_t m_pwmPin;
    int16_t m_lastThrottleVal;

    static const int16_t MIN = 1000;
    static const int16_t MAX = 2000;
};

#endif
