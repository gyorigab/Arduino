#include "controlermessage.h"
#include "trace.h"

ControlerMessage::ControlerMessage() : m_message(Packet::ControlRequest)
{
}

ControlerMessage::~ControlerMessage()
{
}

ControlerMessage& ControlerMessage::createDirectionMsg(const Joystick &joystick)
{
    TRACE_FUNCTION();
    TRACING(DBG);

    Joystick::Data data = joystick.getJoystickPosition();

    ByteBuffer north = ByteBuffer::fromInt(data.upper);
    ByteBuffer south = ByteBuffer::fromInt(data.lower);
    ByteBuffer east  = ByteBuffer::fromInt(data.right);
    ByteBuffer west  = ByteBuffer::fromInt(data.left);

    TRACE_BUF("NORTH: ", north, DBG);
    TRACE_BUF("SOUTH: ", south, DBG);
    TRACE_BUF("EAST:  ", east,  DBG);
    TRACE_BUF("WEST:  ", west,  DBG);

    m_message.set(Message::Direction);
    m_message.set(Message::Direction, Message::North, north);
    m_message.set(Message::Direction, Message::South, south);
    m_message.set(Message::Direction, Message::West,  west);
    m_message.set(Message::Direction, Message::East,  east);

    return *this;
}

ControlerMessage& ControlerMessage::createThrottleMsg(const Joystick &joystick)
{
    TRACE_FUNCTION();
    TRACING(INF);

    Joystick::Data data = joystick.getJoystickPosition();

    ByteBuffer up    = ByteBuffer::fromInt(data.upper);
    ByteBuffer down  = ByteBuffer::fromInt(data.lower);
    ByteBuffer right = ByteBuffer::fromInt(data.right);
    ByteBuffer left  = ByteBuffer::fromInt(data.left);

    TRACE_BUF("UP:    ", up,    DBG);
    TRACE_BUF("DOWN:  ", down,  DBG);
    TRACE_BUF("LEFT:  ", left,  DBG);
    TRACE_BUF("RIGHT: ", right, DBG);

    m_message.set(Message::Throttle);
    m_message.set(Message::Throttle, Message::Up, up);
    m_message.set(Message::Throttle, Message::Down, down);
    m_message.set(Message::Throttle, Message::RotateLeft, left);
    m_message.set(Message::Throttle, Message::RotateRight, right);

    return *this;
}
