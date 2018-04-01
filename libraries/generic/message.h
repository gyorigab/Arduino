#ifndef MESSAGE_H
#define MESSAGE_H

#include "packet.h"
#include "hashmap.h"
#include "bytebuffer.h"
#include "trace.h"

class Message final
{
public:
    enum GID
    {
        MotorControl = 0x4D
    };

    enum RID
    {
        North       = 0x4E,
        South       = 0x53,
        West        = 0x57,
        East        = 0x45,
        Up          = 0x55,
        Down        = 0x44,
        RotateLeft  = 0x4C,
        RotateRight = 0x52
    };

    explicit Message(uint8_t messageType);
    explicit Message(const Packet &packet);

    void set(GID gid, const ByteBuffer &val = ByteBuffer());
    void set(GID gid, RID rid, const ByteBuffer &val);

    ByteBuffer get(GID gid) const;
    ByteBuffer get(GID gid, RID rid) const;

    Packet createPacket() const;
    void parsePacket(const Packet &packet);

private:
    uint8_t m_messageType;
    HashMap m_message;

    int  getLevel(uint8_t separator) const;
    bool isSeparator(uint8_t separator) const;

    ByteBuffer getData(const ByteBuffer &key) const
    {
        return m_message[key];
    }

    void setData(const ByteBuffer &key, const ByteBuffer &value)
    {
        m_message.insert(key,value);
    }

public:
    static const uint8_t GROUP_SEP = 0x1D;
    static const uint8_t RECORD_SEP = 0x1E;
};

#endif
