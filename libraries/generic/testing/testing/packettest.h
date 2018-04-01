#ifndef PACKETTEST_H
#define PACKETTEST_H

#include "../../packet.h"
#include "unittests.h"

using namespace std;

class PacketTest
{
public:
    static void run()
    {
        UnitTests ut;

        uint8_t packet[15] = {0x02,0x43,0x0A,0x00,0x4D,0x4E,0x31,0x53,
                              0x32,0x33,0x57,0x00,0x45,0x34,0x03};

        uint8_t payloadExp[10] = {0x4D,0x4E,0x31,0x53,0x32,
                                  0x33,0x57,0x00,0x45,0x34};

        uint8_t typeExp = 0x43;

        ByteBuffer packetBuffer(packet, 15);
        ByteBuffer payloadBufferExp(payloadExp,10);

        Packet p = decode(packetBuffer);

        ByteBuffer payloadBuff = p.getPayload();
        uint8_t type = p.getType();

        ut.checkEquality(payloadBuff.ptr(), payloadBufferExp.ptr(), 10);
        ut.checkEquality(type,typeExp);

        ByteBuffer packetBufferEncode = encode(p);
        ut.checkEquality(packetBufferEncode.ptr(), packetBuffer.ptr(), 15);

    }
};

#endif // PACKETTEST_H
