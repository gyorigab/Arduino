#ifndef QUADCOPTER_H
#define QUADCOPTRE_H

#include "radio.h"
#include "bytebuffer.h"
#include "joystickdata.h"
#include "message.h"

class Quadcopter
{
public:
    Quadcopter();
    void init();

    JoystickData readDirectionMessage(const Message &msg);
    JoystickData readThrottleMessage(const Message &msg);

    void readMessage(const Message &msg);

    ByteBuffer go();

private:
    Radio m_radio;

    static const ByteBuffer RECV_ADDR;
    static const ByteBuffer TRAN_ADDR;
};

#endif
