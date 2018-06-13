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

    ByteBuffer isButtonPressed(const Joystick::Data &data) const;

     /**
     * \brief Method returns pointer to message which controls dron position
     * \return pointer to message
     */
    Message* getControlerMessage(){return &m_message;}

    bool isThrottleMsgChanged(){ return m_throttleMsgChanged; }
    bool isDirectionMsgChanged(){ return m_directionMsgChanged; }

private:
    Message m_message;

    bool m_directionMsgChanged;
    bool m_throttleMsgChanged;

    Joystick::Data m_lastDirectionData;
    Joystick::Data m_lastThrottleData;
};

#endif // CONTROLERMESSAGE_H
