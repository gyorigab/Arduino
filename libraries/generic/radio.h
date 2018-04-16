#ifndef RADIO_H
#define RADIO_H

#include <RF24_config.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <SPI.h>
#include "bytebuffer.h"

const int ADDRESS_SIZE         = 10;
const int MAX_RECEIVED_BUFFFER = 64;

class Radio final
{
public:

    /**
    * \brief Construct radio object
    *
    * \param address of the transmiter
    * \param address of the receiver
    */
    explicit Radio(ByteBuffer transmiterAddr, ByteBuffer receiverAddr,
                   uint8_t cePin = RADIO_CE_PIN, uint8_t csnPin = RADIO_CSN_PIN);

    ~Radio();

    /**
    * \brief Initialize radio object, open reading and writing pipe
    */
    void init();

    /**
    * \brief Read bytes from radio object
    *
    * \return received byte stream
    */
    ByteBuffer read();

    /**
    * \brief Write byte stream and send it through radio
    *
    * \param byte stream which will be transmited into the receiver
    * \return true if payload was delivered successfuly
    */
    bool write(const ByteBuffer& stream);

private:
    RF24 m_radio;  // Radio object fof the third party library

    ByteBuffer m_transmiterAddr;  // Transmiter address
    ByteBuffer m_receiverAddr;    // Receiver address

    static const uint8_t RADIO_CE_PIN  = 7;  // Byte reserved as group separator
    static const uint8_t RADIO_CSN_PIN = 8; // Byte reserved as record separator
};

#endif
