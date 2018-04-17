#include "motorcontrol.h"

MotorControl::MotorControl(int northPwm, int southPwm, int eastPwm, int westPwm) :
    m_motorNorth(northPwm), m_motorSouth(southPwm), m_motorEast(eastPwm), m_motorWest(westPwm)
{}

MotorControl::~MotorControl()
{}

void MotorControl::init()
{
    m_motorNorth.init();
    m_motorSouth.init();
    m_motorEast.init();
    m_motorWest.init();
}

void MotorControl::drive(const ControlerData& data)
{
    ControlerData::Data directionData = data.getDirectionData();
    ControlerData::Data throttleData = data.getThrottleData();

    // TODO thottle down
    int throttleAll = throttleData.upper;

    int throttleNorth = directionData.upper;
    int throttleSouth = directionData.lower;
    int throttleEast  = directionData.right;
    int throttleWest  = directionData.left;

    // TODO Throttle all + direction must not be over 2000
    m_motorNorth.write(throttleAll + throttleNorth);
    m_motorSouth.write(throttleAll + throttleSouth);
    m_motorEast.write(throttleAll  + throttleEast);
    m_motorWest.write(throttleAll  + throttleWest);
}
