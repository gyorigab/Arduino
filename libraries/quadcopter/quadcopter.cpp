#include <quadcopter.h>
#include "packet.h"
#include "trace.h"
#include "controlerdata.h"
#include "angle.h"

const byte address[][6] = {"00001","00002"};

const ByteBuffer Quadcopter::RECV_ADDR = ByteBuffer(address[0], sizeof(address[0]));
const ByteBuffer Quadcopter::TRAN_ADDR = ByteBuffer(address[1], sizeof(address[1]));

Quadcopter::Quadcopter() : m_radio(RECV_ADDR, TRAN_ADDR)
{

}

void Quadcopter::init()
{
    m_radio.init();
    m_gyroscope.init();
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

    Angle angle = m_gyroscope.getAngle();

    TRACE_VAR("Angle X: ", angle.getX(), DBG);
    TRACE_VAR("Angle Y: ", angle.getY(), DBG);

    return p.getPayload();
}
