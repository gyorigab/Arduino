#include "pid.h"

Pid::Pid()
{}

Pid::~Pid(){}

void Pid::init()
{
    m_timer.init();
}

Angle Pid::getPidCorrection(const Angle &currentAngle,const Angle &desiredAngle )
{
    Angle error = currentAngle - desiredAngle;

    // Proportional part
    m_p = KP * error;

    // Integral part must be provided separately

    float iY = m_i.getY();

    if(-3 < error.getX() < 3)
    {
        float iX = m_i.getX(); + (KI * error.getX());
        m_i.setX(iX);
    }

    if(-3 < error.getY() < 3)
    {
        float iY = m_i.getY(); + (KI * error.getY());
        m_i.setY(iY);
    }

    // Derivative part
    m_d = KD * ((error - m_previousError)/m_timer.getElapsedTime());

    Angle pid = m_p + m_i + m_d;

    cutOverLimits(pid);

    return pid;
}

void Pid::cutOverLimits(Angle &angle)
{
    if(angle.getX() > MAX)
    {
        angle.setX(MAX);
    }

    if(angle.getY() > MAX)
    {
        angle.setY(MAX);
    }

    if(angle.getX() < MIN)
    {
        angle.setX(MIN);
    }

    if(angle.getY() < MIN)
    {
        angle.setY(MIN);
    }
}

