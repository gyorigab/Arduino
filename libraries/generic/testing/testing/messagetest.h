#ifndef MESSAGETEST_H
#define MESSAGETEST_H

#include "../../message.h"
#include "../../bytebuffer.h"
#include "../../packet.h"
#include "unittests.h"

class MessageTest
{
  public:
    static void run()
    {
        UnitTests ut;

        Message m(Packet::ControlRequest);
        Message m1(Packet::ControlRequest);

        uint8_t packet[20] = {0x02,0x43,0x0F,0x00,0x1D,0x64,0x1E,0x4E,0x31,0x1E,
                              0x53,0x32,0x33,0x1E,0x57,0x00,0x1E,0x45,0x34,0x03};

        uint8_t packet1[20] = {0x02,0x43,0x0F,0x00,0x1D,0x64,0x1E,0x4E,0x31,0x1E,
                              0x53,0x32,0x33,0x34,0x1E,0x57,0x1E,0x45,0x34,0x03};

        uint8_t northExp[1] = {0x31};
        uint8_t southExp[2] = {0x32,0x33};
        uint8_t westExp[1]  = {0x00};
        uint8_t eastExp[1]  = {0x34};

        uint8_t northExp1[1] = {0x31};
        uint8_t southExp1[3] = {0x32,0x33,0x34};
        uint8_t westExp1[0]  = {};
        uint8_t eastExp1[1]  = {0x34};

        ByteBuffer northBuffExp(northExp,1);
        ByteBuffer southBuffExp(southExp,2);
        ByteBuffer westBuffExp(westExp,1);
        ByteBuffer eastBuffExp(eastExp,1);

        ByteBuffer northBuffExp1(northExp1,1);
        ByteBuffer southBuffExp1(southExp1,3);
        ByteBuffer westBuffExp1(westExp1,0);
        ByteBuffer eastBuffExp1(eastExp1,1);

        ByteBuffer packetBuffer (packet, 20);
        ByteBuffer packetBuffer1(packet1,20);

        Packet p = decode(packetBuffer);
        Packet p1 = decode(packetBuffer1);

        m.parsePacket(p);
        m1.parsePacket(p1);

        ByteBuffer north = m.get(Message::Direction, Message::North);
        ByteBuffer south = m.get(Message::Direction, Message::South);
        ByteBuffer west  = m.get(Message::Direction, Message::West);
        ByteBuffer east  = m.get(Message::Direction, Message::East);

        ut.checkSizeEquality(north.size(),1);
        ut.checkSizeEquality(south.size(),2);
        ut.checkSizeEquality(west.size(),1);
        ut.checkSizeEquality(east.size(),1);

        ut.checkEquality(north.ptr(), northBuffExp.ptr(),1);
        ut.checkEquality(south.ptr(), southBuffExp.ptr(),2);
        ut.checkEquality(west.ptr(),  westBuffExp.ptr(),1);
        ut.checkEquality(east.ptr(),  eastBuffExp.ptr(),1);

        ByteBuffer north1 = m1.get(Message::Direction, Message::North);
        ByteBuffer south1 = m1.get(Message::Direction, Message::South);
        ByteBuffer west1 = m1.get(Message::Direction,  Message::West);
        ByteBuffer east1  = m1.get(Message::Direction, Message::East);

        ut.checkSizeEquality(north1.size(),1);
        ut.checkSizeEquality(south1.size(),3);
        ut.checkSizeEquality(west1.size(),0);
        ut.checkSizeEquality(east1.size(),1);

        ut.checkEquality(north1.ptr(), northBuffExp1.ptr(),1);
        ut.checkEquality(south1.ptr(), southBuffExp1.ptr(),3);
        ut.checkEquality(west1.ptr(),  westBuffExp1.ptr(),0);
        ut.checkEquality(east1.ptr(),  eastBuffExp1.ptr(),1);

        Message m3(Packet::ControlRequest);

        m3.set(Message::Direction);
        m3.set(Message::Direction, Message::North, northBuffExp);
        m3.set(Message::Direction, Message::South, southBuffExp);
        m3.set(Message::Direction, Message::West,  westBuffExp);
        m3.set(Message::Direction, Message::East,  eastBuffExp);

        Packet p3 = m.createPacket();
        ByteBuffer packetEncode = encode(p3);

        ut.checkSizeEquality(packetEncode.size(), 20);
        ut.checkEquality(packetEncode.ptr(),packetBuffer.ptr(),20);
    }
};

#endif // MESSAGETEST_H
