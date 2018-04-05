#ifndef QUADCOPTER_H
#define QUADCOPTRE_H

#include "radio.h"
#include "bytebuffer.h"
#include "controlerdata.h"
#include "message.h"

class Quadcopter
{
public:
    Quadcopter();
    void init();

    ByteBuffer go();

private:
    Radio m_radio;

    static const ByteBuffer RECV_ADDR;
    static const ByteBuffer TRAN_ADDR;
};

#endif
