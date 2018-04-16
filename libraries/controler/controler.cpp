#include "controler.h"
#include "trace.h"

const byte address[][6] = {"00001","00002"};

const ByteBuffer Controler::RECV_ADDR = ByteBuffer(address[1], sizeof(address[1]));
const ByteBuffer Controler::TRAN_ADDR = ByteBuffer(address[0], sizeof(address[0]));

Controler::Controler() : m_radio(RECV_ADDR, TRAN_ADDR),
    m_directionJoystick(A1,A2,2), m_throttleJoystick(A3,A4,3)
{
}

Controler::~Controler(){}

void Controler::init()
{
    m_directionJoystick.init();
    m_throttleJoystick.init();

    m_radio.init();
}

void Controler::sendMessage(const Message &msg)
{
    TRACE_FUNCTION();
    TRACING(INF);

    // Create packet from message
    Packet p = msg.createPacket();

    TRACE_BUF("Controler payload: ", p.getPayload(), DBG);

    // Encode packet
    ByteBuffer packetEncode = encode(p);

    // Send packet through radio
    m_radio.write(packetEncode);
}

void Controler::go()
{
    ControlerMessage cmsg;

    // Create control message by using data of given joysticks
    cmsg.createDirectionMsg(m_directionJoystick)
        .createThrottleMsg(m_throttleJoystick);

    // Get pointer to controler message which stores control data
    Message *msg = cmsg.getControlerMessage();

    // Send message to dron
    sendMessage(*msg);
}

