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

    if(data == m_lastData)
    {
        ByteBuffer north = ByteBuffer::fromInt(data.upper);
        ByteBuffer south = ByteBuffer::fromInt(data.lower);
        ByteBuffer east  = ByteBuffer::fromInt(data.right);
        ByteBuffer west  = ByteBuffer::fromInt(data.left);

        ByteBuffer button = isButtonPressed(data);

        TRACE_BUF("NORTH:  ", north,  DBG);
        TRACE_BUF("SOUTH:  ", south,  DBG);
        TRACE_BUF("EAST:   ", east,   DBG);
        TRACE_BUF("WEST:   ", west,   DBG);
        TRACE_BUF("BUTTON: ", button, DBG);

        m_message.set(Message::North, north);
        m_message.set(Message::South, south);
        m_message.set(Message::West,  west);
        m_message.set(Message::East,  east);

        m_message.set(Message::ButtonLeft, button);
    }

    m_lastData = data;

    return *this;
}

ControlerMessage& ControlerMessage::createThrottleMsg(const Joystick &joystick)
{
    TRACE_FUNCTION();
    TRACING(DBG);

    Joystick::Data data = joystick.getJoystickPosition();

    if(data == m_lastData)
    {
        ByteBuffer up    = ByteBuffer::fromInt(data.upper);
        ByteBuffer down  = ByteBuffer::fromInt(data.lower);
        ByteBuffer right = ByteBuffer::fromInt(data.right);
        ByteBuffer left  = ByteBuffer::fromInt(data.left);

        ByteBuffer button = isButtonPressed(data);

        TRACE_BUF("UP:     ", up,     DBG);
        TRACE_BUF("DOWN:   ", down,   DBG);
        TRACE_BUF("LEFT:   ", left,   DBG);
        TRACE_BUF("RIGHT:  ", right,  DBG);
        TRACE_BUF("BUTTON: ", button, DBG);

        m_message.set(Message::Up,          up);
        m_message.set(Message::Down,        down);
        m_message.set(Message::RotateLeft,  left);
        m_message.set(Message::RotateRight, right);

        m_message.set(Message::ButtonRight, button);
    }

    m_lastData = data;

    return *this;
}

ByteBuffer ControlerMessage::isButtonPressed(const Joystick::Data &data) const
{
    uint8_t buttonPressed[1] = {0x30};

    if(data.key == true)
    {
        buttonPressed[0] = 0x31;
    }

    return ByteBuffer(buttonPressed, 1);
}
