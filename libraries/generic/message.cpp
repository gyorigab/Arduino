#include "message.h"
#include "trace.h"

Message::Message(uint8_t messageType) : m_messageType(messageType)
{
}

Message::Message(const Packet& packet)
{
    TRACING(DBG);
    TRACE_FUNCTION();

    parsePacket(packet);

}

void Message::set(RID rid, const ByteBuffer& val)
{
    TRACING(INF);

    // TODO Check if element alerady exists is not necessary
    // if(has(rid))

    m_message = m_message.appendUint8(RECORD_SEP).appendUint8(rid).append(val);
}

ByteBuffer Message::get(RID rid) const
{
    ByteBuffer data;

    for(int i = 0; i < m_message.size() - 1; i++)
    {
        if(m_message[i] == RECORD_SEP && m_message[++i] == rid)
        {
            int j = ++i;
            while(m_message[j] != RECORD_SEP && j < m_message.size())
            {
                j++;
            }

            return m_message.slice(i,j);
        }
    }

    return ByteBuffer();
}

bool Message::has(RID rid) const
{
    // TODO TBI
    return true;
}

bool Message::empty() const
{
    return m_message.empty();
}

void Message::clear()
{
    m_message.clear();
    m_messageType = Packet::InvalidType;
}

void Message::parsePacket(const Packet &packet)
{
    TRACING(DBG);
    TRACE_FUNCTION();

    m_messageType = packet.getType();
    m_message = packet.getPayload();

    // invalid message
    if(m_message[0] != RECORD_SEP)
    {
        m_message = ByteBuffer();
        return;
    }
}

Packet Message::createPacket() const
{
    TRACING(INF);
    TRACE_BUF("Message: ", m_message, DBG);

    return Packet(m_messageType, m_message);
}
