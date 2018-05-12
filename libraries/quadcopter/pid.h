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
    static const float KP = 3.55;
    static const float KI = 0.005;
    static const float KD = 2.05;

    static const float MIN = -1000.0;
    static const float MAX =  1000.0;

    Angle m_p;
    Angle m_i;
    Angle m_d;

    Angle m_previousError;

    Timer m_timer;

};

#endif
