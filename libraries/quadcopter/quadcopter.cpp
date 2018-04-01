#include <quadcopter.h>
#include "packet.h"
#include "trace.h"

const byte address[][6] = {"00001","00002"};

const ByteBuffer Quadcopter::RECV_ADDR = ByteBuffer(address[0], sizeof(address[0]));
const ByteBuffer Quadcopter::TRAN_ADDR = ByteBuffer(address[1], sizeof(address[1]));

Quadcopter::Quadcopter() : m_radio(RECV_ADDR, TRAN_ADDR)
{

}

void Quadcopter::init()
{
    m_radio.start();
}

void Quadcopter::readMessage(const Message &msg)
{
    bool hasDirectionData = msg.has(Message::Direction);
    bool hasThrottleData = msg.has(Message::Throttle);

    JoystickData directionData;
    JoystickData throttleData;

    if(hasDirectionData)
    {
        directionData = readDirectionMessage(msg);
    }
    else if(hasThrottleData)
    {
        throttleData  = readThrottleMessage(msg);
    }
    else
    {
        TRACE("Empty received message", WRN);
    }
}

JoystickData Quadcopter::readDirectionMessage(const Message &msg)
{
    TRACE_FUNCTION();

    ByteBuffer north = msg.get(Message::Direction, Message::North);
    ByteBuffer south = msg.get(Message::Direction, Message::South);
    ByteBuffer east  = msg.get(Message::Direction, Message::East);
    ByteBuffer west  = msg.get(Message::Direction, Message::West);

    int n = north.asInt();
    int s = south.asInt();
    int e = east.asInt();
    int w = west.asInt();

    TRACE_VAR("North: ", n, DBG);
    TRACE_VAR("South: ", s, DBG);
    TRACE_VAR("East: ",  e, DBG);
    TRACE_VAR("West: ",  w, DBG);

    return JoystickData(n,s,e,w);
}

JoystickData Quadcopter::readThrottleMessage(const Message &msg)
{
    return JoystickData(0,0,0,0);
}

ByteBuffer Quadcopter::go()
{
    TRACE_FUNCTION();
    ByteBuffer bb = m_radio.read();
    Packet p = decode(bb);

    Message msg(p);

    return p.getPayload();
}
