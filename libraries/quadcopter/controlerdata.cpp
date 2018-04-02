#include "controlerdata.h"

ControlerData::ControlerData(const Message &msg)
{
    readMessage(msg);
}

void ControlerData::readMessage(const Message &msg)
{
    bool hasDirectionData = msg.has(Message::Direction);
    bool hasThrottleData = msg.has(Message::Throttle);

    if(hasDirectionData)
    {
        readDirectionMessage(msg);
    }

    if(hasThrottleData)
    {
        readThrottleMessage(msg);
    }
}

void ControlerData::readDirectionMessage(const Message &msg)
{
    TRACE_FUNCTION();

    ByteBuffer north = msg.get(Message::Direction, Message::North);
    ByteBuffer south = msg.get(Message::Direction, Message::South);
    ByteBuffer east  = msg.get(Message::Direction, Message::East);
    ByteBuffer west  = msg.get(Message::Direction, Message::West);

    m_directionData.upper = north.asInt();
    m_directionData.lower = south.asInt();
    m_directionData.left  = east.asInt();
    m_directionData.right = west.asInt();

    TRACE_VAR("North: ", m_directionData.upper, DBG);
    TRACE_VAR("South: ", m_directionData.lower, DBG);
    TRACE_VAR("East: ",  m_directionData.left, DBG);
    TRACE_VAR("West: ",  m_directionData.right, DBG);
}

void ControlerData::readThrottleMessage(const Message &msg)
{
    TRACE_FUNCTION();

    ByteBuffer up    = msg.get(Message::Throttle, Message::Up);
    ByteBuffer down  = msg.get(Message::Throttle, Message::Down);
    ByteBuffer left  = msg.get(Message::Throttle, Message::RotateLeft);
    ByteBuffer right = msg.get(Message::Throttle, Message::RotateRight);

    m_throttleData.upper = up.asInt();
    m_throttleData.lower = down.asInt();
    m_throttleData.left  = left.asInt();
    m_throttleData.right = right.asInt();

    TRACE_VAR("Up:    ", m_throttleData.upper, DBG);
    TRACE_VAR("Down:  ", m_throttleData.lower, DBG);
    TRACE_VAR("Left:  ", m_throttleData.left,  DBG);
    TRACE_VAR("Right: ", m_throttleData.right, DBG);
}
