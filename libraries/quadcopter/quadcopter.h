#ifndef QUADCOPTER_H
#define QUADCOPTRE_H

#include "radio.h"
#include "bytebuffer.h"
#include "controlerdata.h"
#include "message.h"
#include "gyroscope.h"
#include "pid.h"
#include "motorcontrol.h"

class Quadcopter
{
public:
    Quadcopter();
    void init();

    ByteBuffer go();

private:
    Radio m_radio;
    Gyroscope m_gyroscope;
    Pid m_pid;
    MotorControl m_motors;

    static const ByteBuffer RECV_ADDR;
    static const ByteBuffer TRAN_ADDR;

    static const uint8_t PWM_NORTH = 2;
    static const uint8_t PWM_SOUTH = 5;
    static const uint8_t PWM_EAST  = 93;
    static const uint8_t PWM_WEST  = 94;
};

#endif
