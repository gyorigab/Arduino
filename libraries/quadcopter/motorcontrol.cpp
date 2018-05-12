#include "motorcontrol.h"

typedef ControlerData::Data Data;

MotorControl::MotorControl(uint8_t northPwm, uint8_t southPwm, uint8_t eastPwm, uint8_t westPwm) :
    m_motorNorth(northPwm), m_motorSouth(southPwm), m_motorEast(eastPwm), m_motorWest(westPwm)
{
    m_throttle = 0;
    m_isForecedOff = false;
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
    if(!m_isForecedOff)
    {
        Data currentData = data.getThrottleData();
        Data previousData = m_previousControlerData.getThrottleData();

        m_previousControlerData = data;

        if(currentData.upper != previousData.upper)
        {
            m_throttle = m_throttle + (currentData.upper - previousData.upper);
        }

        if(currentData.lower != previousData.lower)
        {
            m_throttle = m_throttle - (currentData.lower - previousData.lower);
        }

        m_motorNorth.write(m_throttle);
        m_motorSouth.write(m_throttle);
        m_motorEast.write(m_throttle);
        m_motorWest.write(m_throttle);
    }
}

Angle MotorControl::direction(const ControlerData& data)
{
    ControlerData::Data directionData = data.getDirectionData();

    int throttleNorth = directionData.upper;
    int throttleSouth = directionData.lower;
    int throttleEast  = directionData.right;
    int throttleWest  = directionData.left;

    // TODO transform data to angle

    // TODO Throttle all + direction must not be over 2000
    m_motorNorth.write(m_throttle);
    m_motorSouth.write(m_throttle);
    m_motorEast.write(m_throttle);
    m_motorWest.write(m_throttle);
}

void MotorControl::startStopEngines(const ControlerData &data)
{
    TRACING(DBG);

    Data throttleData = data.getThrottleData();

    TRACE_VAR("Throttle data key: ", throttleData.key, DBG);

    if(throttleData.key == true)
    {
        if(m_throttle > MOTOR_OFF)
        {
            m_isForecedOff = true;
            stopEngines();
        }
        else
        {
            m_isForecedOff = false;
            startEngines();
        }
    }
}

void MotorControl::startEngines()
{
    m_throttle = MOTOR_START;
    throttle(m_throttle);
}

void MotorControl::stopEngines()
{
    m_throttle = MOTOR_OFF;
    throttle(m_throttle);
}


void MotorControl::throttle(int t)
{
    TRACING(DBG);
    TRACE_VAR("Throttle for all motors: ", m_throttle, DBG);

    if(!m_isForecedOff)
    {
        m_throttle = t;

        m_motorNorth.write(t);
        m_motorSouth.write(t);
        m_motorEast.write(t);
        m_motorWest.write(t);
    }
}

void MotorControl::control(const Angle &angle)
{
    TRACING(DBG);

    if(!m_isForecedOff)
    {
        TRACE_VAR("THROTLE X: ", m_throttle + angle.getX(), DBG);
        TRACE_VAR("THROTLE Y: ", m_throttle - angle.getX(), DBG);

        m_motorNorth.write(m_throttle - angle.getX());
        m_motorSouth.write(m_throttle + angle.getX());
        m_motorEast.write(m_throttle  - angle.getY());
        m_motorWest.write(m_throttle  + angle.getY());
    }
}
