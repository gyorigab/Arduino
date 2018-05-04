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

    ControlerData();
    ControlerData(const Message &msg);

    void readMessage(const Message &msg);

    void readDirectionMessage(const Message &msg);
    void readThrottleMessage(const Message &msg);

    const Data& getDirectionData() const { return m_directionData; }
    const Data& getThrottleData() const { return m_throttleData; }

    void setDirectionData(const Data& data)
    {
        m_directionData.upper = data.upper;
        m_directionData.lower = data.lower;
        m_directionData.left  = data.left;
        m_directionData.right = data.right;
        m_directionData.key   = data.key;
    }

    void setThrottleData(const Data& data)
    {
        m_throttleData.upper = data.upper;
        m_throttleData.lower = data.lower;
        m_throttleData.left  = data.left;
        m_throttleData.right = data.right;
        m_throttleData.key   = data.key;
    }

private:
    Data m_directionData;
    Data m_throttleData;
};

#endif
