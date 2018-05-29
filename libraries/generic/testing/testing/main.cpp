#include "bytebuffertest.h"
#include "packettest.h"
#include "hashmaptest.h"
#include "messagetest.h"
#include "messagetestext.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Byte Buffer" << endl;
    ByteBufferTest::run();

    cout << "Packet" << endl;
    PacketTest::run();

    cout << "Hash Map" << endl;
    HashMapTest::run();

    cout << "Message" << endl;
    MessageTest::run();

    cout << "MessageExt" << endl;
    MessageTestExt::run();

    cout << "Serialize message" << endl;
    //srandom(time(0));
    //MessageTest::serialzieTest();
}
