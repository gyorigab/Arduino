#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#include "motor.h"
#include "controlerdata.h"
#include "angle.h"

class MotorControl final
{
public:
    MotorControl(int northPwm, int southPwm, int eastPwm, int westPwm);
    ~MotorControl();

    void init();
    void throttle(const ControlerData &data);
    Angle direction(const ControlerData &data);
    void throttle(int t);
    void startEngines();
    void control(const Angle &angle);

private:

    Motor m_motorNorth;
    Motor m_motorSouth;
    Motor m_motorWest;
    Motor m_motorEast;

    int m_throttle;
};

#endif
