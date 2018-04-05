#include "controler.h"
#include "trace.h"

const byte address[][6] = {"00001","00002"};

const ByteBuffer Controler::RECV_ADDR = ByteBuffer(address[1], sizeof(address[1]));
const ByteBuffer Controler::TRAN_ADDR = ByteBuffer(address[0], sizeof(address[0]));

Controler::Controler() : m_radio(RECV_ADDR, TRAN_ADDR),
    m_directionJoystick(A1,A2,2), m_throttleJoystick(A3,A4,3)
{

}

void Controler::init()
{
    m_directionJoystick.init();
    m_throttleJoystick.init();

    m_radio.start();
}

void Controler::sendMessage(const Message &msg)
{
    TRACE_FUNCTION();

    Packet p = msg.createPacket();

    TRACE_VAR("Payload: ", p.getPayload().cptr(), DBG);

    ByteBuffer packetEncode = encode(p);

    m_radio.write(packetEncode);
}

void Controler::go()
{
    ControlerMessage cmsg;

    cmsg.createDirectionMsg(m_directionJoystick)
        .createThrottleMsg(m_throttleJoystick);

    Message *msg = cmsg.getControlerMessage();

    sendMessage(*msg);
}

