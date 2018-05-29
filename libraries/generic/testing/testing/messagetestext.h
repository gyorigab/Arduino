#ifndef MESSAGETESTEXT_H
#define MESSAGETESTEXT_H

#include "../../messageext.h"
#include "../../bytebuffer.h"
#include "../../packet.h"
#include "unittests.h"

class MessageTestExt
{
  public:
    static void run()
    {
        UnitTests ut;

        MessageExt m(Packet::ControlRequest);
        MessageExt m1(Packet::ControlRequest);

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

        ByteBuffer north = m.get(MessageExt::Direction, MessageExt::North);
        ByteBuffer south = m.get(MessageExt::Direction, MessageExt::South);
        ByteBuffer west  = m.get(MessageExt::Direction, MessageExt::West);
        ByteBuffer east  = m.get(MessageExt::Direction, MessageExt::East);

        ut.checkSizeEquality(north.size(),1);
        ut.checkSizeEquality(south.size(),2);
        ut.checkSizeEquality(west.size(),1);
        ut.checkSizeEquality(east.size(),1);

        ut.checkEquality(north.ptr(), northBuffExp.ptr(),1);
        ut.checkEquality(south.ptr(), southBuffExp.ptr(),2);
        ut.checkEquality(west.ptr(),  westBuffExp.ptr(),1);
        ut.checkEquality(east.ptr(),  eastBuffExp.ptr(),1);

        ByteBuffer north1 = m1.get(MessageExt::Direction, MessageExt::North);
        ByteBuffer south1 = m1.get(MessageExt::Direction, MessageExt::South);
        ByteBuffer west1 = m1.get(MessageExt::Direction,  MessageExt::West);
        ByteBuffer east1  = m1.get(MessageExt::Direction, MessageExt::East);

        ut.checkSizeEquality(north1.size(),1);
        ut.checkSizeEquality(south1.size(),3);
        ut.checkSizeEquality(west1.size(),0);
        ut.checkSizeEquality(east1.size(),1);

        ut.checkEquality(north1.ptr(), northBuffExp1.ptr(),1);
        ut.checkEquality(south1.ptr(), southBuffExp1.ptr(),3);
        ut.checkEquality(west1.ptr(),  westBuffExp1.ptr(),0);
        ut.checkEquality(east1.ptr(),  eastBuffExp1.ptr(),1);

        MessageExt m3(Packet::ControlRequest);

        m3.set(MessageExt::Direction);
        m3.set(MessageExt::Direction, MessageExt::North, northBuffExp);
        m3.set(MessageExt::Direction, MessageExt::South, southBuffExp);
        m3.set(MessageExt::Direction, MessageExt::West,  westBuffExp);
        m3.set(MessageExt::Direction, MessageExt::East,  eastBuffExp);

        Packet p3 = m.createPacket();
        ByteBuffer packetEncode = encode(p3);

        ut.checkSizeEquality(packetEncode.size(), 20);
        ut.checkEquality(packetEncode.ptr(),packetBuffer.ptr(),20);
    }

    static void serialzieTest()
    {
        UnitTests ut;

        const int ARRAY_SIZE = 4;

        int directionVal;
        int throttleVal;

        int directionArray[ARRAY_SIZE] = {0};
        int throttleArray[ARRAY_SIZE]  = {0};

        int directionArrayReceived[ARRAY_SIZE] = {0};
        int throttleArrayReceived[ARRAY_SIZE]  = {0};

        for(int i=0; i<100; i++)
        {
            // Transmiter part
            for(int j=0; j<ARRAY_SIZE; j++)
            {
                directionArray[j] = 0;
                throttleArray[j] = 0;
            }

            for(int j=0; j<ARRAY_SIZE; j++)
            {
                //directionVal = int(double(10000)*rand()/(RAND_MAX+1.0));
                //throttleVal = int(double(10000)*rand()/(RAND_MAX+1.0));
                directionVal = j;
                throttleVal  = j+10;

                directionArray[j] = directionVal;
                throttleArray[j] = throttleVal;
            }

            /*cout << "Transmitted \n";

            cout << "North: " << directionArray[0] << endl;
            cout << "South: " << directionArray[1] << endl;
            cout << "East:  " << directionArray[2] << endl;
            cout << "West:  " << directionArray[3] << endl;

            cout << "Up:    " << throttleArray[0] << endl;
            cout << "Down:  " << throttleArray[1] << endl;
            cout << "Right: " << throttleArray[2] << endl;
            cout << "Left:  " << throttleArray[3] << endl;*/

            ByteBuffer tNorth = ByteBuffer::fromInt(directionArray[0]);
            ByteBuffer tSouth = ByteBuffer::fromInt(directionArray[1]);
            ByteBuffer tEast  = ByteBuffer::fromInt(directionArray[2]);
            ByteBuffer tWest  = ByteBuffer::fromInt(directionArray[3]);

            ByteBuffer tUp    = ByteBuffer::fromInt(throttleArray[0]);
            ByteBuffer tDown  = ByteBuffer::fromInt(throttleArray[1]);
            ByteBuffer tRight = ByteBuffer::fromInt(throttleArray[2]);
            ByteBuffer tLeft  = ByteBuffer::fromInt(throttleArray[3]);

            MessageExt tMessage(Packet::ControlRequest);

            tMessage.set(MessageExt::Direction);
            tMessage.set(MessageExt::Direction, MessageExt::North, tNorth);
            tMessage.set(MessageExt::Direction, MessageExt::South, tSouth);
            tMessage.set(MessageExt::Direction, MessageExt::East,  tEast);
            tMessage.set(MessageExt::Direction, MessageExt::West,  tWest);

            tMessage.set(MessageExt::Throttle);
            tMessage.set(MessageExt::Throttle, MessageExt::Up,          tUp);
            tMessage.set(MessageExt::Throttle, MessageExt::Down,        tDown);
            tMessage.set(MessageExt::Throttle, MessageExt::RotateLeft,  tLeft);
            tMessage.set(MessageExt::Throttle, MessageExt::RotateRight, tRight);

            Packet pt = tMessage.createPacket();
            ByteBuffer packetEncode = encode(pt);

            ByteBuffer ptb = pt.getPayload();

            // Receiver part

            Packet pr = decode(packetEncode);

            ByteBuffer ptr = pr.getPayload();

            ut.checkSizeEquality(ptb.size(),ptr.size());
            ut.checkEquality(ptb.ptr(),ptr.ptr(),ptb.size());

            MessageExt rMessage(pr);

            ByteBuffer rNorth = rMessage.get(MessageExt::Direction, MessageExt::North);
            ByteBuffer rSouth = rMessage.get(MessageExt::Direction, MessageExt::South);
            ByteBuffer rEast  = rMessage.get(MessageExt::Direction, MessageExt::East);
            ByteBuffer rWest  = rMessage.get(MessageExt::Direction, MessageExt::West);

            ByteBuffer rUp    = rMessage.get(MessageExt::Throttle, MessageExt::Up);
            ByteBuffer rDown  = rMessage.get(MessageExt::Throttle, MessageExt::Down);
            ByteBuffer rRight = rMessage.get(MessageExt::Throttle, MessageExt::RotateRight);
            ByteBuffer rLeft  = rMessage.get(MessageExt::Throttle, MessageExt::RotateLeft);

            directionArrayReceived[0] = rNorth.asInt();
            directionArrayReceived[1] = rSouth.asInt();
            directionArrayReceived[2] = rEast.asInt();
            directionArrayReceived[3] = rWest.asInt();
            
            throttleArrayReceived[0] = rUp.asInt();
            throttleArrayReceived[1] = rDown.asInt();
            throttleArrayReceived[2] = rRight.asInt();
            throttleArrayReceived[3] = rLeft.asInt();

            /*cout << "Received \n";

            cout << "North: " << directionArrayReceived[0]  << endl;
            cout << "South: " << directionArrayReceived[1]  << endl;
            cout << "East:  " << directionArrayReceived[2]  << endl;
            cout << "West:  " << directionArrayReceived[3]  << endl;

            cout << "Up:    " << throttleArrayReceived[0]  << endl;
            cout << "Down:  " << throttleArrayReceived[1]  << endl;
            cout << "Right: " << throttleArrayReceived[2]  << endl;
            cout << "Left:  " << throttleArrayReceived[3]  << endl;*/

            ut.checkEquality(directionArray[0], directionArrayReceived[0]);
            ut.checkEquality(directionArray[1], directionArrayReceived[1]);
            ut.checkEquality(directionArray[2], directionArrayReceived[2]);
            ut.checkEquality(directionArray[3], directionArrayReceived[3]);

            ut.checkEquality(throttleArray[0], throttleArrayReceived[0]);
            ut.checkEquality(throttleArray[1], throttleArrayReceived[1]);
            ut.checkEquality(throttleArray[2], throttleArrayReceived[2]);
            ut.checkEquality(throttleArray[3], throttleArrayReceived[3]);
        }
    }
};

#endif // MESSAGETEST_H
