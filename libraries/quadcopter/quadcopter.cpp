#include <quadcopter.h>
#include "packet.h"
#include "trace.h"
#include "controlerdata.h"
#include "angle.h"
#include "motor.h"

const byte address[][6] = {"00001","00002"};

const ByteBuffer Quadcopter::RECV_ADDR = ByteBuffer(address[0], sizeof(address[0]));
const ByteBuffer Quadcopter::TRAN_ADDR = ByteBuffer(address[1], sizeof(address[1]));

Motor m1(3);
Motor m2(5);

Quadcopter::Quadcopter() : m_radio(RECV_ADDR, TRAN_ADDR), m_motors(PWM_NORTH, PWM_SOUTH, PWM_WEST, PWM_EAST)
{

}

void Quadcopter::init()
{
    m_radio.init();
    m_gyroscope.init();
    m_pid.init();
    m_motors.init();

    //m1.init();
    //m2.init();

    // Let the HW init
    delay(1000);

    // Start Engines
    m_motors.startEngines();
}

ByteBuffer Quadcopter::go()
{
    TRACE_FUNCTION();
    TRACING(INF);

    ByteBuffer bb = m_radio.read();
    Packet p = decode(bb);

    Message msg(p);

    ControlerData cdata(msg);

    TRACE_BUF("Data Payload Received ",p.getPayload(), DBG );

    Angle currentDronAngle = m_gyroscope.getAngle();

    TRACE_VAR("Angle X: ", currentDronAngle.getX(), DBG);
    TRACE_VAR("Angle Y: ", currentDronAngle.getY(), DBG);

    // TODO for test purposes just get drone to horizontal position
    Angle desriedDronAngle(0.0, 0.0);

    Angle pid = m_pid.getPidCorrection(currentDronAngle, desriedDronAngle);

    TRACE_VAR("PID correction X: ", pid.getX(), INF);
    TRACE_VAR("PID correction Y: ", pid.getY(), INF);

    m_motors.throttle(1700);
    m_motors.control(pid);

    return p.getPayload();
}
