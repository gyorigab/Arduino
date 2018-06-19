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

double Timer::getElapsedTime()
{
    double currentTime = millis();
    double elapsedTime = (currentTime - m_previousTime) / 1000;

    m_previousTime = currentTime;

    return elapsedTime;
}
