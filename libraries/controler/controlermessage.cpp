#include "controlermessage.h"
#include "trace.h"

ControlerMessage::ControlerMessage() : m_message(Packet::ControlRequest)
{
    m_directionMsgChanged = false;
    m_throttleMsgChanged  = false;
}

ControlerMessage::~ControlerMessage()
{
}

ControlerMessage& ControlerMessage::createDirectionMsg(const Joystick &joystick)
{
    Joystick::Data data = joystick.getJoystickPosition();

    if(data != m_lastDirectionData)
    {
        m_directionMsgChanged = true;
        m_message.clear();

        m_message.set(Message::North, ByteBuffer::fromInt(data.upper));
        m_message.set(Message::South, ByteBuffer::fromInt(data.lower));
        m_message.set(Message::West,  ByteBuffer::fromInt(data.left));
        m_message.set(Message::East,  ByteBuffer::fromInt(data.right));

        m_message.set(Message::ButtonLeft, isButtonPressed(data));
    }
    else
    {
        m_directionMsgChanged = false;
    }

    m_lastDirectionData = data;

    return *this;
}

ControlerMessage& ControlerMessage::createThrottleMsg(const Joystick &joystick)
{
    Joystick::Data data = joystick.getJoystickPosition();

    if(data != m_lastThrottleData)
    {
        m_throttleMsgChanged = true;
        m_message.clear();

        m_message.set(Message::Up,          ByteBuffer::fromInt(data.upper));
        m_message.set(Message::Down,        ByteBuffer::fromInt(data.lower));
        m_message.set(Message::RotateLeft,  ByteBuffer::fromInt(data.left));
        m_message.set(Message::RotateRight, ByteBuffer::fromInt(data.right));

        m_message.set(Message::ButtonRight, isButtonPressed(data));
    }
    else
    {
        m_throttleMsgChanged = false;
    }

    m_lastThrottleData = data;

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
