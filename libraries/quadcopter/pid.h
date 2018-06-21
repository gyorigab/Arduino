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
    static const float KP = 2.00;
    static const float KI = 1.00;
    static const float KD = 1.00;

    static const float MIN = -200.0;
    static const float MAX =  200.0;

    static const float INTEGRAL_LIMIT = 3.0;

    Angle m_p;
    Angle m_i;
    Angle m_d;

    Angle m_previousError;

    Timer m_timer;

};

#endif
