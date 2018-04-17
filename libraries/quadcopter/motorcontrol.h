#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include "motor.h"
#include "controlerdata.h"

class MotorControl final
{
public:
    MotorControl(int northPwm, int southPwm, int eastPwm, int westPwm);
    ~MotorControl();

    void init();
    void drive(const ControlerData &data);

private:

    Motor m_motorNorth;
    Motor m_motorSouth;
    Motor m_motorWest;
    Motor m_motorEast;
};

#endif
