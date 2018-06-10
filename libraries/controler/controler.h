#ifndef CONTROLER_H
#define CONTROLER_H

#include "radio.h"
#include "bytebuffer.h"
#include "joystick.h"
#include "message.h"
#include "controlermessage.h"

class Controler final
{
public:
    Controler();
    ~Controler();

    /**
    * \brief Init hw controler parts (joysticks, radio...)
    */
    void init();


    /**
    * \brief Method creates and encodes packet from given message and sents it to radio
    * \param message with dron control data
    */

    void sendMessage(const Message &msg);

    /**
    * \brief Method called in arduino main loop
    */
    void go();

private:

    Radio m_radio;  // Instance of radio HW object to send and receive dron control data

    Joystick m_directionJoystick;  // Instance of joystick to control dron direction
    Joystick m_throttleJoystick;   // Instance of joystick to control dron throtle

    static const ByteBuffer RECV_ADDR;  // Receiver radio address
    static const ByteBuffer TRAN_ADDR;  // Transmitter radio address

    ControlerMessage m_cmsg;
};

#endif
