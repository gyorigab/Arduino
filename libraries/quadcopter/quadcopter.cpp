#include <quadcopter.h>
#include "packet.h"
#include "trace.h"
#include "motor.h"

const byte address[][6] = {"00001","00002"};

const ByteBuffer Quadcopter::RECV_ADDR = ByteBuffer(address[0], sizeof(address[0]));
const ByteBuffer Quadcopter::TRAN_ADDR = ByteBuffer(address[1], sizeof(address[1]));

const uint8_t DRONE_RADIO_CE  = 48;
const uint8_t DRONE_RADIO_CSN = 49;

Quadcopter::Quadcopter() : m_radio(RECV_ADDR, TRAN_ADDR, DRONE_RADIO_CE, DRONE_RADIO_CSN),
                           m_motors(PWM_NORTH, PWM_SOUTH, PWM_EAST, PWM_WEST)
{

}

void Quadcopter::init()
{
    m_radio.init();
    m_gyroscope.init();
    m_pid.init();
    m_motors.init();

    // Let the HW init
    delay(1000);

    // Start Engines
    m_motors.startEngines();
    m_desriedDronAngle = Angle(0.0, 0.0);
}

ByteBuffer Quadcopter::go()
{
    TRACE_FUNCTION();
    TRACING(INF);

    ByteBuffer bb = m_radio.read();

    //TODO check
    Angle currentDronAngle = m_gyroscope.getAngle();

    TRACE_VAR("Angle X: ", currentDronAngle.getX(), DBG);
    TRACE_VAR("Angle Y: ", currentDronAngle.getY(), DBG);

    if(!bb.empty())
    {
        TRACE_BUF("Received packet:", bb, DBG);

        Packet p = decode(bb);

        Message msg(p);

        ControlerData cdata(msg);

        TRACE_BUF("Data Payload Received ",p.getPayload(), DBG );

        //m_motors.startStopEngines(cdata);
        m_motors.throttle(cdata);

        m_desriedDronAngle = m_motors.direction(cdata);
    }

    Angle pid = m_pid.getPidCorrection(currentDronAngle, m_desriedDronAngle);

    m_motors.control(pid);

    //TRACE_MEM();

    return ByteBuffer();
}
