#ifndef PID_H
#define PID_H

#include "timer.h"
#include "angle.h"

class Pid
{
public:
    struct Data
    {
        int upper;
        int lower;
        int left;
        int right;

        Data() : upper(0), lower(0), left(0), right(0) {}
    };

    Pid();
    ~Pid();

    void init();
    Angle getPidCorrection(const Angle &currentAngle,const Angle &desiredAngle );

private:
    static const double KP = 3.55;
    static const double KI = 0.005;
    static const double KD = 2.05;

    Angle m_p;
    Angle m_i;
    Angle m_d;

    Angle m_previousError;

    Timer m_timer;

};

#endif
