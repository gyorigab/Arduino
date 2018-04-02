#ifndef CONTROLERDATA_H
#define CONTROLERDATA_H

#include "trace.h"
#include "message.h"

class ControlerData final
{
public:
    struct JoystickData
    {
        int upper;
        int lower;
        int left;
        int right;

        bool key;

        JoystickData() : upper(0), lower(0), left(0), right(0), key(false) {}
    };

    ControlerData(const Message &msg);

    void readMessage(const Message &msg);

    void readDirectionMessage(const Message &msg);
    void readThrottleMessage(const Message &msg);

    JoystickData getDirectionData(){return m_directionData;}
    JoystickData getThrottleData(){return m_throttleData;}

private:
    JoystickData m_directionData;
    JoystickData m_throttleData;
};

#endif
