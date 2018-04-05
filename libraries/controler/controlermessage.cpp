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

    Joystick::Data data = joystick.getJoystickPosition();

    ByteBuffer north = ByteBuffer::fromInt(data.upper);
    ByteBuffer south = ByteBuffer::fromInt(data.lower);
    ByteBuffer east  = ByteBuffer::fromInt(data.right);
    ByteBuffer west  = ByteBuffer::fromInt(data.left);

    TRACE_VAR("NORTH: ", north.cptr(), DBG);
    TRACE_VAR("SOUTH: ", south.cptr(), DBG);
    TRACE_VAR("EAST:  ", east.cptr(),  DBG);
    TRACE_VAR("WEST:  ", west.cptr(),  DBG);

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

    Joystick::Data data = joystick.getJoystickPosition();

    ByteBuffer up    = ByteBuffer::fromInt(data.upper);
    ByteBuffer down  = ByteBuffer::fromInt(data.lower);
    ByteBuffer right = ByteBuffer::fromInt(data.right);
    ByteBuffer left  = ByteBuffer::fromInt(data.left);

    TRACE_VAR("UP:    ", up.cptr(),    DBG);
    TRACE_VAR("DOWN:  ", down.cptr(),  DBG);
    TRACE_VAR("LEFT:  ", left.cptr(),  DBG);
    TRACE_VAR("RIGHT: ", right.cptr(), DBG);

    m_message.set(Message::Throttle);
    m_message.set(Message::Throttle, Message::Up, up);
    m_message.set(Message::Throttle, Message::Down, down);
    m_message.set(Message::Throttle, Message::RotateLeft, left);
    m_message.set(Message::Throttle, Message::RotateRight, right);

    return *this;
}
