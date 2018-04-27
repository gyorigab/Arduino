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

    double iY = m_i.getY();

    if(-3 < error.getX() < 3)
    {
        double iX = m_i.getX(); + (KI * error.getX());
        m_i.setX(iX);
    }

    if(-3 < error.getY() < 3)
    {
        double iY = m_i.getY(); + (KI * error.getY());
        m_i.setY(iY);
    }

    // Derivative part
    m_d = KD * ((error - m_previousError)/m_timer.getElapsedTime());

    return m_p + m_i + m_d;
}

