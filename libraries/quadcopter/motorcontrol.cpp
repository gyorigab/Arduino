#include "motorcontrol.h"

MotorControl::MotorControl(int northPwm, int southPwm, int eastPwm, int westPwm) :
    m_motorNorth(northPwm), m_motorSouth(southPwm), m_motorEast(eastPwm), m_motorWest(westPwm)
{
    m_throttle = 0;
}

MotorControl::~MotorControl()
{}

void MotorControl::init()
{
    m_motorNorth.init();
    m_motorSouth.init();
    m_motorEast.init();
    m_motorWest.init();
}

void MotorControl::throttle(const ControlerData& data)
{
    ControlerData::Data directionData = data.getDirectionData();
    ControlerData::Data throttleData = data.getThrottleData();

    // TODO thottle down
    m_throttle = throttleData.upper;

    int throttleNorth = directionData.upper;
    int throttleSouth = directionData.lower;
    int throttleEast  = directionData.right;
    int throttleWest  = directionData.left;

    // TODO Throttle all + direction must not be over 2000
    m_motorNorth.write(m_throttle + throttleNorth);
    m_motorSouth.write(m_throttle + throttleSouth);
    m_motorEast.write(m_throttle  + throttleEast);
    m_motorWest.write(m_throttle  + throttleWest);
}

void MotorControl::startEngines()
{
    m_throttle = 1300;
    throttle(m_throttle);
}

void MotorControl::throttle(int t)
{
    m_throttle = t;

    m_motorNorth.write(t);
    m_motorSouth.write(t);
    m_motorEast.write(t);
    m_motorWest.write(t);
}

void MotorControl::control(const Angle &angle)
{
    m_motorNorth.write(m_throttle + angle.getX());
    m_motorSouth.write(m_throttle - angle.getX());
    m_motorEast.write(m_throttle  + angle.getY());
    m_motorWest.write(m_throttle  - angle.getY());
}
