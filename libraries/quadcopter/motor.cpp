#include "motor.h"
#include <Arduino.h>

Motor::Motor(uint8_t pwmPin) : m_pwmPin(pwmPin), m_lastThrottleVal(0)
{}

Motor::~Motor()
{
    if(m_servo.attached())
    {
        m_servo.detach();
    }
}

void Motor::init()
{
    if(m_servo.attached())
    {
        m_servo.detach();
    }

    m_servo.attach(m_pwmPin, MIN, MAX);

    m_servo.writeMicroseconds(MIN);
}

int Motor::cutOverLimits(int16_t rawThrottle)
{
    if(rawThrottle < MIN)
    {
        return MIN;
    }
    else if(rawThrottle > MAX)
    {
        return MAX;
    }
    else
    {
        return rawThrottle;
    }
}

void Motor::write(int16_t inpThrottle)
{
    // cut values which are over limits
    int throttle = cutOverLimits(inpThrottle);

    if(throttle != m_lastThrottleVal)
    {
        int increment = 1;
        int diff = throttle - m_lastThrottleVal;

        if(throttle < m_lastThrottleVal)
        {
            increment = -1;
            diff *= -1;
        }

        // Throttle smoothly
        for(int i = 0; i < diff; i++)
        {
            m_lastThrottleVal += increment;
            m_servo.writeMicroseconds(m_lastThrottleVal);
            //delay(10);
        }
    }
}
