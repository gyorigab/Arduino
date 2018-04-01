#ifndef BYTEBUFFERTEST_H
#define BYTEBUFFERTEST_H

#include <iostream>
#include "../../bytebuffer.h"
#include "unittests.h"
#include <stdint.h>


using namespace std;

class ByteBufferTest
{
  public:

    static void run()
    {
        UnitTests ut;

        // ======== Constructor, operator ==========

        uint8_t input1[3] = {0x00, 0xFF, 0x02};
        uint8_t input2[2] = {0xAA, 0xBB};
        uint8_t input3[1] = {0xCC};

        ByteBuffer test1;
        ByteBuffer test2(input2, 2);
        ByteBuffer test3(input3, 1);

        test1 = ByteBuffer(input1,3);

        ut.checkSizeEquality(test1.size(), 3);
        ut.checkEquality(test1.ptr(), input1, 3);

        ut.checkSizeEquality(test2.size(), 2);
        ut.checkEquality(test2.ptr(), input2, 2);

        // ================== Append ===============

        ByteBuffer appendBuf1;

        uint8_t exp1[5] = {0x00, 0xFF, 0x02, 0xAA, 0xBB};
        appendBuf1 = test1.append(test2);

        ut.checkSizeEquality(appendBuf1.size(), 5);
        ut.checkEquality(appendBuf1.ptr(), exp1, 5);

        ByteBuffer appendBuf2;

        uint8_t exp2[6] = {0x00, 0xFF, 0x02, 0xAA, 0xBB, 0xCC};
        appendBuf2 = test1.append(test2).append(test3);

        ut.checkSizeEquality(appendBuf2.size(), 6);
        ut.checkEquality(appendBuf2.ptr(), exp2, 6);

        ByteBuffer appendBuf3;
        ByteBuffer test4(input1, 3);
        uint8_t exp6[4] = {0x00, 0xFF, 0x02, 0xCC};

        appendBuf3 = test4.appendUint8(0xCC);

        ut.checkSizeEquality(appendBuf3.size(), 4);
        ut.checkEquality(appendBuf3.ptr(), exp6, 4);

        // ================== Slice ================

        ByteBuffer sliceBuf1;
        uint8_t input4[6] = {0x00, 0xFF, 0x02, 0xAA, 0xBB, 0xCC};
        ByteBuffer toSlice(input4, 6);

        uint8_t exp3[6] = {0xFF, 0x02, 0xAA,};
        sliceBuf1 = toSlice.slice(1,4);

        ut.checkSizeEquality(sliceBuf1.size(), 3);
        ut.checkEquality(sliceBuf1.ptr(), exp3, 3);

        ByteBuffer sliceBuf2;
        sliceBuf2 = toSlice.slice(0,6);

        ut.checkSizeEquality(sliceBuf2.size(), 6);
        ut.checkEquality(sliceBuf2.ptr(), exp2, 6);

        ByteBuffer sliceBuf3;
        sliceBuf3 = toSlice.slice(0,0);

        ut.checkSizeEquality(sliceBuf3.size(), 0);

        ByteBuffer sliceBuf4;
        sliceBuf4 = toSlice.slice(1,0);
        ut.checkSizeEquality(sliceBuf4.size(), 0);

        ByteBuffer sliceBuf5;
        uint8_t exp4[1] = { 0xCC };
        sliceBuf5 = toSlice.slice(5,6);

        ut.checkSizeEquality(sliceBuf5.size(), 1);
        ut.checkEquality(sliceBuf5.ptr(), exp4, 1);

        ByteBuffer sliceBuf6;
        uint8_t exp5[2] = { 0x02, 0xAA };
        sliceBuf6 = toSlice.slice(1,5).slice(1,3);

        ut.checkSizeEquality(sliceBuf6.size(), 2);
        ut.checkEquality(sliceBuf6.ptr(), exp5, 2);

        // =========== Equality operator ===========

        ut.checkEquality(true,  test1 == test1);
        ut.checkEquality(false, test1 == test2);

        // =================== Get =================

        ByteBuffer test6(input1, 3);

        ut.checkEquality(test6.get(0), 0x00);
        ut.checkEquality(test6.get(-1),0x00);
        ut.checkEquality(test6.get(3), 0x00);
        ut.checkEquality(test6.get(1), 0xFF);
        ut.checkEquality(test6.get(2), 0x02);

        // ============ Conversions ==============

        const char * ascii = "12A";
        ByteBuffer asciiBuffer = ByteBuffer::fromAscii(ascii,3);

        uint8_t expAsciiBuff[3] = {0x31,0x32,0x41};

        ut.checkSizeEquality(asciiBuffer.size(), 3);
        ut.checkEquality(asciiBuffer.ptr(),expAsciiBuff, 3);

        ByteBuffer asciiBuffer1(expAsciiBuff, 2);

        char * ascii1 = new char[2];

        asciiBuffer1.asAscii(ascii1, 2);

        cout << "Ascii: " << ascii1 << endl;

        delete[] ascii1;

        const char * hexStr = "DEADBEAF";

        ByteBuffer hexBuffer = ByteBuffer::fromHex(hexStr,8);

        uint8_t expHexBuff[4] = {0xDE,0xAD,0xBE,0xAF};

        ut.checkSizeEquality(hexBuffer.size(), 4);
        ut.checkEquality(hexBuffer.ptr(),expHexBuff, 4);

        int testInt = 1234;

        ByteBuffer testIntCharBuff= ByteBuffer::fromInt(testInt);

        uint8_t expIntBuff[4] = {0x31, 0x32, 0x33, 0x34};

        ut.checkSizeEquality(testIntCharBuff.size(), 4);
        ut.checkEquality(testIntCharBuff.ptr(),expIntBuff, 4);

        ByteBuffer testCharIntBuff(expIntBuff, 4);

        ut.checkSizeEquality(testCharIntBuff.asInt(),testInt);
    }
};

#endif // BYTEBUFFERTEST_H
