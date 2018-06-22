#ifndef PID_H
#define PID_H

#include "timer.h"
#include "angle.h"

class Pid
{
public:
    Pid();
    ~Pid();

    void init();
    Angle getPidCorrection(const Angle &currentAngle, const Angle &desiredAngle);
    void cutOverLimits(Angle &angle);

private:
    static const float KP;
    static const float KI;
    static const float KD;

    static const float MIN;
    static const float MAX;

    static const float INTEGRAL_LIMIT;

    Angle m_p;
    Angle m_i;
    Angle m_d;

    Angle m_previousError;

    Timer m_timer;
};

#endif
