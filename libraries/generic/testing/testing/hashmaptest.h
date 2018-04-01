#ifndef HASHMAPTEST_H
#define HASHMAPTEST_H

#include "../../hashmap.h"
#include "../../bytebuffer.h"
#include "unittests.h"

class HashMapTest
{
public:
    static void run()
    {
        HashMap h;
        UnitTests ut;

        uint8_t key1[1] = {0x01};
        uint8_t key2[2] = {0x02,0x03};
        uint8_t key3[1] = {0x04};
        uint8_t key4[1] = {0x05};

        uint8_t val1[1] = {0x10};
        uint8_t val2[2] = {0x11,0x12};
        uint8_t val3[2] = {0x13,0x14};

        ByteBuffer keyBuff1(key1,1);
        ByteBuffer keyBuff2(key2,2);
        ByteBuffer keyBuff3(key3,1);
        ByteBuffer keyBuff4(key4,1);

        ByteBuffer valBuff1(val1,1);
        ByteBuffer valBuff2(val2,2);
        ByteBuffer valBuff3(val3,2);

        ut.checkEquality(h.empty(),true);

        h.insert(keyBuff1,valBuff1);

        ut.checkEquality(h.empty(),false);
        ut.checkSizeEquality( h.capacity(), 1024 );
        ut.checkSizeEquality( h.size(), 1 );

        h.insert(keyBuff2,valBuff2);
        h.insert(keyBuff3,valBuff3);

        ut.checkSizeEquality( h.capacity(), 1024 );
        ut.checkSizeEquality( h.size(), 3 );

        // Alerady exist
        h.insert(keyBuff2,valBuff2);

        ut.checkSizeEquality( h.size(), 3 );

        ut.checkEquality(h.exists(keyBuff1),true);
        ut.checkEquality(h.exists(keyBuff2),true);
        ut.checkEquality(h.exists(keyBuff3),true);
        ut.checkEquality(h.exists(keyBuff4),false);

        ut.checkEquality(h[keyBuff1].ptr(), valBuff1.ptr(),1);
        ut.checkEquality(h[keyBuff2].ptr(), valBuff2.ptr(),2);
        ut.checkEquality(h[keyBuff3].ptr(), valBuff3.ptr(),2);
    }
};

#endif // HASHMAPTEST_H
