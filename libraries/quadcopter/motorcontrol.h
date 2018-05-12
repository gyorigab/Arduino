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
    void startStopEngines(const ControlerData &data);
    void throttle(int t);
    void startEngines();
    void stopEngines();
    void control(const Angle &angle);

private:

    static const int MOTOR_OFF   = 1000;
    static const int MOTOR_START = 1300;

    Motor m_motorNorth;
    Motor m_motorSouth;
    Motor m_motorWest;
    Motor m_motorEast;

    int m_throttle;
    bool m_isForecedOff;

    ControlerData m_previousControlerData;

};

#endif
