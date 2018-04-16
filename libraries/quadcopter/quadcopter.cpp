#include <quadcopter.h>
#include "packet.h"
#include "trace.h"
#include "controlerdata.h"


const byte address[][6] = {"00001","00002"};

const ByteBuffer Quadcopter::RECV_ADDR = ByteBuffer(address[0], sizeof(address[0]));
const ByteBuffer Quadcopter::TRAN_ADDR = ByteBuffer(address[1], sizeof(address[1]));

Quadcopter::Quadcopter() : m_radio(RECV_ADDR, TRAN_ADDR)
{

}

void Quadcopter::init()
{
    m_radio.init();
}

ByteBuffer Quadcopter::go()
{
    TRACE_FUNCTION();
    TRACING(DBG);

    ByteBuffer bb = m_radio.read();
    Packet p = decode(bb);

    Message msg(p);

    ControlerData cdata(msg);

    TRACE_BUF("Data Payload Received",p.getPayload(), DBG );

    return p.getPayload();
}
