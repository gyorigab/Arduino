#ifndef CONTROLERDATA_H
#define CONTROLERDATA_H

#include "trace.h"
#include "message.h"

class ControlerData final
{
public:
    struct Data
    {
        uint8_t upper;
        uint8_t lower;
        uint8_t left;
        uint8_t right;

        bool key;

        Data() : upper(0), lower(0), left(0), right(0), key(false) {}
    };

    ControlerData();
    ControlerData(const Message &msg);

    void readMessage(const Message &msg);

    void readDirectionMessage(const Message &msg);
    void readThrottleMessage(const Message &msg);

    const Data& getDirectionData() const { return m_directionData; }
    const Data& getThrottleData() const { return m_throttleData; }

    bool isButtonPressed(const ByteBuffer &button) const;

    void setDirectionData(const Data& data)
    {
        m_directionData = data;
    }

    void setThrottleData(const Data& data)
    {
        m_throttleData = data;
    }

private:
    Data m_directionData;
    Data m_throttleData;
};

#endif
