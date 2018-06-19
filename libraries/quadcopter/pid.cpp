#include "pid.h"
#include "trace.h"

Pid::Pid()
{}

Pid::~Pid(){}

void Pid::init()
{
    m_timer.init();
}

Angle Pid::getPidCorrection(const Angle &currentAngle,const Angle &desiredAngle )
{
    TRACING(DBG);

    Angle error = currentAngle - desiredAngle;

    TRACE_VAR("Error X: ", error.getX(), DBG);
    TRACE_VAR("Error Y: ", error.getY(), DBG);

    // Proportional part
    m_p = KP * error;

    TRACE_VAR("Proportional part X: ", m_p.getX(), DBG);
    TRACE_VAR("Proportional part Y: ", m_p.getY(), DBG);

    // Integral part must be provided separately
    if(-3.0 < error.getX() && error.getX() < 3.0)
    {
        double iX = m_i.getX() + (KI * error.getX());
        m_i.setX(iX);
        TRACE_VAR("Integral part X: ", m_i.getX(), DBG);

    }

    if(-3.0 < error.getY() && error.getY() < 3.0)
    {
        double iY = m_i.getY() + (KI * error.getY());
        m_i.setY(iY);
        TRACE_VAR("Integral part Y: ", m_i.getY(), DBG);

    }

    double elapsedTime = m_timer.getElapsedTime();
    // Derivative part
    m_d = KD * ((error - m_previousError)/elapsedTime);

    TRACE_VAR("Elapsed time [s]:  ", elapsedTime, DBG);
    TRACE_VAR("Derivative part X: ", m_d.getX(), DBG);
    TRACE_VAR("Derivative part Y: ", m_d.getY(), DBG);

    m_previousError = error;

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

