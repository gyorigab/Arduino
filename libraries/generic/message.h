#ifndef MESSAGE_H
#define MESSAGE_H

#include "packet.h"
#include "hashmap.h"
#include "bytebuffer.h"
#include "trace.h"

/* Message fromat
 * 1 byte GID separtor
 * 1 byte GID indentificator
 * n bytes data of GID (optional)
 * 1 byte RID separator
 * 1 byte RID identificator
 * n bytes data of RID
 * ...
 */

class Message final
{
public:
    enum GID
    {
        Direction = 0x64,
        Throttle  = 0x74
    };

    enum RID
    {
        North       = 0x4E,
        South       = 0x53,
        West        = 0x57,
        East        = 0x45,
        Up          = 0x55,
        Down        = 0x44,
        RotateLeft  = 0x4C,
        RotateRight = 0x52
    };

    /**
     * \brief Creates empty message
     * \param packet type e.g. control request
     */
    explicit Message(uint8_t messageType);

    /**
     * \brief Creates message by parsing given packet
     * \param packet which stores data
     */
    explicit Message(const Packet &packet);

    /**
     * \brief Set group ID and its data
     * \param group ID identificator
     * \param group data
     */
    void set(GID gid, const ByteBuffer &val = ByteBuffer());

    /**
     * \brief Set record ID and its data. This record ID belongs to given GID
     * \param group ID identificator
     * \param record ID identificator
     * \param record data
     */
    void set(GID gid, RID rid, const ByteBuffer &val);

    /**
     * \brief Get data of given group ID
     * \param group ID identificator
     * \return group data belonged to given GID
     */
    ByteBuffer get(GID gid) const;

    /**
     * \brief Get data of given record ID which belnongs to given group ID
     * \param group ID identificator
     * \param record ID identificator
     * \return record data belonged to given RID and GID
     */
    ByteBuffer get(GID gid, RID rid) const;

    /**
     * \brief Check existence of GID identificator
     * \param group ID identificator
     * \return true if exists
     */
    bool has(GID gid) const;

    /**
     * \brief Check existence of RID identificator which belongs to given GID
     * \param group ID identificator
     * \param record ID identificator
     * \return true if exists
     */
    bool has(GID gid, RID rid) const;

    /**
     * \brief Create packet payload string from given GIDs and RIDs
     * \return instance of packet with type and payload
     */
    Packet createPacket() const;

    /**
     * \brief Parse given packet and fill the local data structure in
     * \param Packet
     */
    void parsePacket(const Packet &packet);

private:
    uint8_t m_messageType; // Message type = Packet Type
    HashMap m_message;     // Internal key value message data structure


    /**
     * \brief Get level of the separator
     * \return 0 - GID sep, 1 - RID sep, -1 - NONE
     */
    int  getLevel(uint8_t separator) const;

    /**
     * \brief Check if given byte is separator
     * \return true if it is
     */
    bool isSeparator(uint8_t separator) const;

    /**
     * \brief Get data of given internal key
     * \param internal key (string composed from GID and/or RID)
     * \return message data
     */
    ByteBuffer getData(const ByteBuffer &key) const
    {
        return m_message[key];
    }

    /**
     * \brief Set data for given internal key
     * \param internal key (string composed from GID and/or RID)
     * \param data to store for given key
     */
    void setData(const ByteBuffer &key, const ByteBuffer &value)
    {
        TRACING(INF);

        if( !m_message.insert(key,value) )
        {
            TRACE("Message capacity is full", ERR);
        }
    }

public:
    static const uint8_t GROUP_SEP = 0x1D;  // Byte reserved as group separator
    static const uint8_t RECORD_SEP = 0x1E; // Byte reserved as record separator
};

#endif
