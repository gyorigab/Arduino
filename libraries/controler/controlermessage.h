#ifndef CONTROLERMESSAGE_H
#define CONTROLERMESSAGE_H

#include "joystick.h"
#include "message.h"

class ControlerMessage
{
public:
     ControlerMessage();
    ~ControlerMessage();

    ControlerMessage& createDirectionMsg(const Joystick &joystick);
    ControlerMessage& createThrottleMsg(const Joystick &joystick);

    Message* getControlerMessage(){return &m_message;}

private:
    Message m_message;
};

#endif // CONTROLERMESSAGE_H
