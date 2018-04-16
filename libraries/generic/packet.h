#ifndef PACKET_H
#define PACKET_H

#ifndef GDEBUG
#include <Arduino.h>
#endif

#include "bytebuffer.h"
#include "trace.h"

/*
 1 byte  - STX
 1 byte  - type of the packet
 2 bytes - payload length
 n bytes - payload
 1 byte  - ETX

 // TODO CRC in future
*/

class Packet final
{
public:
    enum PacketType
    {
        InvalidType = 0x00,
        ControlRequest = 0x43
    };

    /**
    * \brief Initialize packet
    * \param type of the packet e.g. controlRequest
    * \param payload of the packet
    */
    Packet(uint8_t type = InvalidType, ByteBuffer payload = ByteBuffer()) : m_type(type), m_payload(payload){}


    /**
    * \brief Function returns payload of the packet
    * \return packet payload
    */
    const ByteBuffer& getPayload() const
    {
        return m_payload;
    }

    /**
    * \brief Function returns type of the packet
    * \return packet type
    */
    uint8_t getType() const
    {
        return m_type;
    }

private:
    uint8_t m_type;
    ByteBuffer m_payload;

public:
    static const uint8_t STX = 0x02;
    static const uint8_t ETX = 0x03;
};

/**
* \brief Decode byte stream into the packet
* \param stream which contains packet frame, packet type data length and data itself
* \return instance of packet
*/
inline Packet decode(ByteBuffer &src)
{
    TRACE_FUNCTION();

    size_t i = 0;

    // Searching first STX (in case of invalid data front of)
    while (i < src.size() && src.get(i) != Packet::STX)
    {
        ++i;
    }

    // Get rid of invalid data
    src = src.slice(i, src.size());

    // Packet cannot be shorter than 4 bytes
    if (src.size() < 4)
    {
       return Packet();
    }

    // Get payload size
    uint16_t payloadLength = src.getUint16LE(2);

    // Checking of packet validity
    if (src.size() < 4U + payloadLength + 1U)
    {
        return Packet();
    }

    // Get message type
    uint8_t type = src.get(1);
    // Get payload
    ByteBuffer payload = src.slice(4, 4 + payloadLength);
    // Get ETX
    uint8_t expectedEtx = src.get(4 + payloadLength);

    if (expectedEtx != Packet::ETX)
    {
        // Invalid packet
    }

    return Packet(type, payload);
}

/**
* \brief Encode packet into the byte stream
* \param instance of packet
* \return stream which contains packet frame, packet type data length and data itself
*/
inline ByteBuffer encode(const Packet &packet)
{
    TRACE_FUNCTION();

    ByteBuffer data = ByteBuffer()
            .appendUint8(packet.getType())
            .appendUint16LE(packet.getPayload().size())
            .append(packet.getPayload());

    return ByteBuffer()
            .appendUint8(Packet::STX)
            .append(data)
            .appendUint8(Packet::ETX);
}

#endif
