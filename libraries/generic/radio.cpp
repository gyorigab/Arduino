#include "radio.h"

Radio::Radio(ByteBuffer transmiterAddr, ByteBuffer receiverAddr) : m_radio(7,8)
{
    m_transmiterAddr = transmiterAddr;
    m_receiverAddr   = receiverAddr;
}

Radio::~Radio()
{

}

void Radio::start()
{
    m_radio.begin();
    m_radio.openWritingPipe(m_transmiterAddr.ptr());
    m_radio.openReadingPipe(1, m_receiverAddr.ptr());

    m_radio.setPALevel(RF24_PA_MIN);
}

ByteBuffer Radio::read()
{
    m_radio.startListening();

    if (m_radio.available())
    {
        uint8_t text[MAX_RECEIVED_BUFFFER] = "";
        m_radio.read(&text, sizeof(text));

        return ByteBuffer(&text[0], sizeof(text));
    }
    else
    {
        return ByteBuffer();
    }
}

bool Radio::write(const ByteBuffer& stream)
{
    m_radio.stopListening();
    return m_radio.write(stream.ptr(), stream.size());
}
