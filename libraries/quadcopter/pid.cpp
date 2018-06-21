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
    double dT   = m_timer.getTimeDiff();

    TRACE_VAR("Error X: ", error.getX(), DBG);
    TRACE_VAR("Error Y: ", error.getY(), DBG);

    // Proportional part
    m_p = KP * error;

    TRACE_VAR("Proportional part X: ", m_p.getX(), DBG);
    TRACE_VAR("Proportional part Y: ", m_p.getY(), DBG);

    // Integral part must be provided separately
    if(-INTEGRAL_LIMIT < error.getX() && error.getX() < INTEGRAL_LIMIT)
    {
        double iX = m_i.getX() + error.getX() * dT;
        m_i.setX(KI * iX);

        TRACE_VAR("Integral part X: ", m_i.getX(), DBG);

    }

    if(-INTEGRAL_LIMIT < error.getY() && error.getY() < INTEGRAL_LIMIT)
    {
        double iY = m_i.getY() + error.getY() * dT;
        m_i.setY(KI * iY);

        TRACE_VAR("Integral part Y: ", m_i.getY(), DBG);

    }

    // Derivative part
    m_d = KD * ((error - m_previousError)/dT);

    TRACE_VAR("Elapsed time [s]:  ", dT, DBG);
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

