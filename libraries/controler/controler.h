#ifndef CONTROLER_H
#define CONTROLER_H

#include "radio.h"
#include "bytebuffer.h"
#include "joystick.h"
#include "message.h"

class Controler
{
public:
    Controler();
    void init();

    Message getDirectionMsg();
    Message getThrottleMsg();

    void sendMessage(const Message &msg);
    void go();

private:

    Radio m_radio;

    Joystick m_directionJoystick;
    Joystick m_throttleJoystick;

    static const ByteBuffer RECV_ADDR;
    static const ByteBuffer TRAN_ADDR;
};

#endif
