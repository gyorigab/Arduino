#include "timer.h"
#include <Arduino.h>

Timer::Timer()
{
    m_previousTime = 0;
}

Timer::~Timer()
{}

void Timer::init()
{
    m_previousTime = 0;
}

double Timer::getTimeDiff()
{
    double currentTime = millis();
    double timeDiff = (currentTime - m_previousTime) / 1000;

    m_previousTime = currentTime;

    return timeDiff;
}
