#ifndef MESSAGE_H
#define MESSAGE_H

#include "packet.h"
#include "hashmap.h"
#include "bytebuffer.h"
#include "trace.h"

/* Message fromat
 * 1 byte RID separator
 * 1 byte RID identificator
 * n bytes data of RID
 * ...
 */

class Message final
{
public:

    enum RID
    {
        North       = 0x4E,
        South       = 0x53,
        West        = 0x57,
        East        = 0x45,
        Up          = 0x55,
        Down        = 0x44,
        RotateLeft  = 0x4C,
        RotateRight = 0x52,
        ButtonLeft  = 0x42,
        ButtonRight = 0x62
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
     * \brief Set record ID and its data
     * \param record ID identificator
     * \param record data
     */
    void set(RID rid, const ByteBuffer &val = ByteBuffer());

    /**
     * \brief Get data of given record ID
     * \param record ID identificator
     * \return record data belonged to given GID
     */
    ByteBuffer get(RID rid) const;

    /**
     * \brief Check existence of RID identificator
     * \param record ID identificator
     * \return true if exists
     */
    bool has(RID rid) const;

    /**
     * \brief Check if message is empty
     * \return true if message is empty
     */
    bool empty() const;

    void clear();

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
    uint8_t    m_messageType; // Message type = Packet Type
    ByteBuffer m_message;     // Internal key value message data structure

public:
    static const uint8_t RECORD_SEP = 0x1E; // Byte reserved as record separator
};

#endif
