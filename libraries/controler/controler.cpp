#include "controler.h"
#include "trace.h"

const byte address[][6] = {"00001","00002"};

const ByteBuffer Controler::RECV_ADDR = ByteBuffer(address[1], sizeof(address[1]));
const ByteBuffer Controler::TRAN_ADDR = ByteBuffer(address[0], sizeof(address[0]));

Controler::Controler() : m_radio(RECV_ADDR, TRAN_ADDR),
    m_directionJoystick(A0,A1,2), m_throttleJoystick(A2,A3,3)
{

}

void Controler::init()
{
    m_directionJoystick.init();
    m_throttleJoystick.init();

    m_radio.start();
}

Message Controler::getDirectionMsg()
{
    TRACE_FUNCTION();

    Message msg(Packet::ControlRequest);

    Joystick::Data data = m_directionJoystick.getJoystickPosition();

    ByteBuffer north = ByteBuffer::fromInt(data.upper);
    ByteBuffer south = ByteBuffer::fromInt(data.lower);
    ByteBuffer east  = ByteBuffer::fromInt(data.right);
    ByteBuffer west  = ByteBuffer::fromInt(data.left);

    msg.set(Message::MotorControl);
    msg.set(Message::MotorControl, Message::North, north);
    msg.set(Message::MotorControl, Message::South, south);
    msg.set(Message::MotorControl, Message::West,  west);
    msg.set(Message::MotorControl, Message::East,  east);

    return msg;
}

void Controler::sendMessage(const Message &msg)
{
    TRACE_FUNCTION();

    Packet p = msg.createPacket();

    TRACE_VAR("Payload: ", p.getPayload().cptr(), DBG);
    TRACE_VAR("Payload: ", p.getPayload().cptr(), WRN);
    TRACE_VAR("Payload: ", p.getPayload().cptr(), ERR);

    ByteBuffer packetEncode = encode(p);

    m_radio.write(packetEncode);
}

void Controler::go()
{
    Message msg = getDirectionMsg();
    sendMessage(msg);
}

