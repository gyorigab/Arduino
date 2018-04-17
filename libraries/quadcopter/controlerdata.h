#ifndef CONTROLERDATA_H
#define CONTROLERDATA_H

#include "trace.h"
#include "message.h"

class ControlerData final
{
public:
    struct Data
    {
        int upper;
        int lower;
        int left;
        int right;

        bool key;

        Data() : upper(0), lower(0), left(0), right(0), key(false) {}
    };

    ControlerData(const Message &msg);

    void readMessage(const Message &msg);

    void readDirectionMessage(const Message &msg);
    void readThrottleMessage(const Message &msg);

    const Data& getDirectionData() const { return m_directionData; }
    const Data& getThrottleData() const { return m_throttleData; }

private:
    Data m_directionData;
    Data m_throttleData;
};

#endif
