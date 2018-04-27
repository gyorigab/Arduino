#include "timer.h"
#include <Arduino.h>

Timer::Timer()
{
    m_timeCurr = m_timePrev = 0;
}

Timer::~Timer()
{}

void Timer::init()
{
    m_timePrev = 0;
    m_timeCurr = millis();
}

double Timer::getElapsedTime()
{
    m_timePrev = m_timeCurr;
    m_timeCurr = millis();

    return (m_timeCurr - m_timePrev) / 1000;
}
