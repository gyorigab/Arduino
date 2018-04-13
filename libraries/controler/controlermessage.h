#ifndef CONTROLERMESSAGE_H
#define CONTROLERMESSAGE_H

#include "joystick.h"
#include "message.h"

class ControlerMessage
{
public:
    ControlerMessage();
    ~ControlerMessage();

     /**
     * \brief Method creates message to control dron direction
     * \param instance of joystick
     * \param message which stores direction data
     */
    ControlerMessage& createDirectionMsg(const Joystick &joystick);


     /**
     * \brief Method creates message to control dron altitude
     * \param instance of joystick
     * \param message which stores throttle data
     */
    ControlerMessage& createThrottleMsg(const Joystick &joystick);

     /**
     * \brief Method returns pointer to message which controls dron position
     * \return pointer to message
     */
    Message* getControlerMessage(){return &m_message;}

private:
    Message m_message;
};

#endif // CONTROLERMESSAGE_H
