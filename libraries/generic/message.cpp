#include "message.h"
#include "trace.h"

Message::Message(uint8_t messageType) : m_messageType(messageType)
{
}

Message::Message(const Packet& packet)
{
    if (!packet.getPayload().empty())
    {
       parsePacket(packet);
    }
}

void Message::set(GID gid, const ByteBuffer& val)
{
    ByteBuffer key;
    key = key.appendUint8(gid);

    setData(key,val);
}

void Message::set(GID gid, RID rid, const ByteBuffer& val)
{
    ByteBuffer key;
    key = key.appendUint8(gid).appendUint8(rid);

    setData(key,val);
}

ByteBuffer Message::get(GID gid) const
{
    ByteBuffer key;
    key = key.appendUint8(gid);

    return getData(key);
}

ByteBuffer Message::get(GID gid, RID rid) const
{
    ByteBuffer key;
    key = key.appendUint8(gid).appendUint8(rid);

    return getData(key);
}

bool Message::has(GID gid) const
{
    ByteBuffer key;
    key = key.appendUint8(gid);

    return m_message.exists(key);
}

bool Message::has(GID gid, RID rid) const
{
    ByteBuffer key;
    key = key.appendUint8(gid).appendUint8(rid);

    return m_message.exists(key);
}

int Message::getLevel(uint8_t separator) const
{
    switch (separator)
    {
        case GROUP_SEP:  return  0;
        case RECORD_SEP: return  1;
        default:         return -1;
    }
}

bool Message::isSeparator(uint8_t separator) const
{
    return separator == GROUP_SEP || separator == RECORD_SEP;
}

void Message::parsePacket(const Packet &packet)
{
    ByteBuffer buffer = packet.getPayload();
    ByteBuffer value;
    ByteBuffer key;

    if(buffer.empty() || buffer[0] != GROUP_SEP)
    {
        return;
    }

    for(int i = 0; i < buffer.size(); i++)
    {
        int level = getLevel(buffer[i]);

        if(level == 0)
        {
            key = ByteBuffer();
        }
        else if(level == 1)
        {
            key = key.slice(0,1);
        }

        if(!isSeparator(buffer.get(i)))
        {
            if(i < buffer.size())
            {
                key = key.appendUint8(buffer[i]);
            }

            for(int j = i + 1; j < buffer.size(); j++)
            {
                if(!isSeparator(buffer[j]))
                {
                    value = value.appendUint8(buffer[j]);
                }
                else
                {
                    i = j - 1;
                    break;
                }
            }

            m_message.insert(key,value);
            value = ByteBuffer();
        }
    }
}

Packet Message::createPacket() const
{
    TRACING(INF);

    ByteBuffer message;

    for(int i = 0; i < m_message.size(); i++)
    {
        ByteBuffer key = m_message.getKey(i);
        ByteBuffer val = m_message.getValue(i);

        if(key.size() == 1)
        {
            if(val.size() == 0)
            {
                message = message.appendUint8(GROUP_SEP).appendUint8(key.get(0));
            }
            else
            {
                message = message.appendUint8(GROUP_SEP).appendUint8(key.get(0)).append(val);
            }
        }
        else if (key.size() == 2)
        {
            if(val.size() == 0)
            {
                message = message.appendUint8(RECORD_SEP).appendUint8(key.get(1));
            }
            else
            {
                message = message.appendUint8(RECORD_SEP).appendUint8(key.get(1)).append(val);
            }
        }
    }

    TRACE_BUF("Message: ", message.cptr(), DBG);

    return Packet(m_messageType, message);
}
