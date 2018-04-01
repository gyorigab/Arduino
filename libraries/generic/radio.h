#ifndef radio_h
#define radio_h

#include <RF24_config.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <SPI.h>
#include "bytebuffer.h"

const int ADDRESS_SIZE         = 10;
const int MAX_RECEIVED_BUFFFER = 64;

class Radio
{
public:
    explicit Radio(ByteBuffer transmiterAddr, ByteBuffer receiverAddr);
    void start();

    ByteBuffer read();
    bool write(const ByteBuffer& stream);

    ~Radio();
private:
    RF24 m_radio;

    // Transmiter address
    ByteBuffer m_transmiterAddr;
    // Receiver address
    ByteBuffer m_receiverAddr;
};

#endif
