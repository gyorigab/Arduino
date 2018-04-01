#ifndef BYTEBUFFER_H
#define BYTEBUFFER_H

#ifdef GDEBUG
#include <stdint.h>
#include <cstddef>
#include <stdio.h>
#endif

/**
 * \brief An array of bytes.
 *
 * The data is allocated on the heap. Each instance makes its own copy of the data in constructor.
 * This class is not thread-safe.
 *
 * \invariant m_length == 0 iff m_data == nullptr
 *
 */

static uint8_t hexDigitValue(char c);

class ByteBuffer final
{
public:

    /**
     * \brief Creates an empty byte buffer.
     */
    ByteBuffer() : ByteBuffer(0)
    {
    }

    /**
     * \brief Deallocates the memory.
     */
    ~ByteBuffer()
    {
        clear();
    }

    /**
    * \brief Creates a byte buffer by copying \c length bytes from the memory pointed to by \c src
    * \param src the pointer to the source data
    * \param length the number of bytes to copy from \c src
    */
    ByteBuffer(const uint8_t *src, size_t length) : ByteBuffer(length)
    {
        if (length > 0 && src != NULL)
        {
            //memcpy( m_data, src, length);
            for(int i = 0; i < m_length; i++)
            {
                m_data[i] = src[i];
            }
        }
    }

    /**
     * \brief Assigment operator overloading
     */
    ByteBuffer &operator=(const ByteBuffer &src)
    {
        if (&src != this)
        {
            delete[] m_data;

            m_length = src.m_length;
            m_data = m_length ? new uint8_t[m_length] : NULL;

            for(int i = 0; i < m_length; i++)
            {
                m_data[i] = src.m_data[i];
            }
        }

        return *this;
    }

    /**
     * \brief Copy constructor
     */
    ByteBuffer(const ByteBuffer &src)
    {
        // Bohuzal neni k dispozici swap
        m_length = src.m_length;
        m_data = m_length ? new uint8_t[m_length] : NULL;

        for(int i = 0; i < m_length; i++)
        {
            m_data[i] = src.m_data[i];
        }
    }

    /**
     * \brief Overloading of equality operator for comparison content of two byte arrays
     * \return true if all items of both buffers are equal
     */
    bool operator==(const ByteBuffer& buff)
    {
        if(m_length != buff.m_length)
        {
            return false;
        }

        for(int i = 0; i < m_length; i++)
        {
            if(m_data[i] != buff.m_data[i])
            {
                return false;
            }
        }
        return true;
    }

    uint8_t operator[](size_t index) const
    {
        return get(index);
    }

    /**
     * \brief Returns a pointer to the start of the byte buffer.
     * \return a pointer to the start of the byte buffer or \c nullptr if the buffer is empty
     */
    const uint8_t *ptr() const
    {
        return m_data;
    }

    const char *cptr() const
    {
        return (char*)m_data;
    }

    /**
     * \brief Returns the number of bytes in the byte buffer.
     * \return the number of bytes in the byte buffer
     */
    size_t size() const
    {
        return m_length;
    }

    /**
     * \brief Returns \c true if the byte buffer is empty.
     * \return \c true if the byte buffer is empty
     */
    bool empty() const
    {
        return size() == 0;
    }

    /**
    * \brief Returns the byte on the position indicated by the \c index parameter.
    *
    * \param index the zero-based position of the byte to return
    * \return the byte on the index-th position
    */
    uint8_t get(size_t index) const
    {
        if(index >= 0 && index < m_length)
        {
            return m_data[index];
        }
        return 0x00;
    }

    /**
     * \brief Returns the unsigned 16-bit integer (encoded in little endian) on the position indicated by \c offset.
     *
     * \param index the zero-based position of the unsigned 16-bit integer to return
     * \return the unsigned 16-bit integer
     */
    uint16_t getUint16LE(size_t offset) const
    {
        return get(offset) | (get(offset + 1) << 8);
    }

    /**
     * \brief Returns a byte buffer containing a slice of this byte buffer.
     *
     * \param start the zero-based position of the start of the slice
     * \param end the zero-based position of the byte just after the end of the slice
     * \return a byte buffer containing the bytes in the interval [start, end)
     */
    ByteBuffer slice(size_t start, size_t end) const
    {
        if(start >= 0 && start <= m_length && end >= start && end <= m_length)
        {
            ByteBuffer bb(end - start);
            if (bb.m_length > 0)
            {
                for(size_t i = start, j = 0; j < end - start ; i++, j++)
                {
                    bb.m_data[j] = m_data[i];
                }
            }
            return bb;
        }
        else
        {
            return ByteBuffer();
        }
    }

    /**
    * \brief Creates a new byte buffer by appending another byte buffer to the content of this byte buffer.
    * \param buf the byte buffer to append
    * \return the new byte buffer
    */
    ByteBuffer append(const uint8_t *src, size_t length) const
    {
        ByteBuffer bb(m_length + length);
        int j = 0;

        for(int i = 0; i < m_length; i++, j++ )
        {
            bb.m_data[j] = m_data[i];
        }

        for(int i = 0; i < length; i++, j++ )
        {
            bb.m_data[j] = src[i];
        }

        return bb;
    }

    /**
     * \brief Creates a new byte buffer by appending another byte buffer to the content of this byte buffer.
     * \param buf the byte buffer to append
     * \return the new byte buffer
     */
    ByteBuffer append(const ByteBuffer &buf) const
    {
        return append(buf.m_data, buf.m_length);
    }

    /**
     * \brief Creates a new byte buffer by appending a byte to the content of this byte buffer.
     * \param value the byte to append
     * \return the new byte buffer
     */
    ByteBuffer appendUint8(uint8_t value) const
    {
        return append(&value, 1);
    }
    /**
     * \brief Creates a new byte buffer by appending a little endian encoding of a 16-bit unsigned value
     * to the content of this byte buffer.
     * \param value the value to append
     * \return the new byte buffer
     */
    ByteBuffer appendUint16LE(uint16_t value) const
    {
        uint8_t buf[2] = { static_cast<uint8_t>(value & 0xFF), static_cast<uint8_t>(value >> 8) };
        return append(buf, 2);
    }

    /**
     * \brief Creates a new byte buffer by appending a big endian encoding of a 16-bit unsigned value
     * to the content of this byte buffer.
     * \param value the value to append
     * \return the new byte buffer
     */
    ByteBuffer appendUint16BE(uint16_t value) const
    {
        uint8_t buf[2] = { static_cast<uint8_t>(value >> 8), static_cast<uint8_t>(value & 0xFF) };
        return append(buf, 2);
    }

    /**
     * \brief Constructs a byte buffer by parsing a hex string.
     * \param hex a hex string
     * \return the byte buffer
     * \throws Exception if the parameter is not a valid hex string
     */
    static ByteBuffer fromHex(const char* hex, size_t len)
    {
        if (len % 2 == 1)
        {
            return ByteBuffer();
        }
        ByteBuffer bb(len / 2);

        for (size_t i = 0; i < bb.m_length; ++i)
        {
            bb.m_data[i] = (hexDigitValue(hex[2 * i]) << 4) | hexDigitValue(hex[2 * i + 1]);
        }

        return bb;
    }

    /**
     * \brief Constructs a byte buffer from an ASCII string.
     * \param ascii an ASCII string
     * \return the byte buffer
     * \throws Exception if the parameters contains non-ASCII characters
     */
    static ByteBuffer fromAscii(const char* ascii, size_t len)
    {
        ByteBuffer bb(len);
        for (size_t i = 0; i < bb.m_length; ++i)
        {
            char c = ascii[i];
            if (c < 0 || c > 127)
            {
                return ByteBuffer();
            }
            bb.m_data[i] = c;
        }
        return bb;
    }

    /**
     * \brief Returns an ASCII string made from the bytes in the buffer.
     * \return an ASCII string
     * \throws Exception if the buffer contains bytes outside of the ASCII charset (>= 128)
     */
    void asAscii(char* string, size_t len) const
    {
        for (size_t i = 0; i < m_length; i++)
        {
            if (m_data[i] > 127)
            {
                return;
            }
            string[i] = static_cast<char>(m_data[i]);
        }
    }

    /**
     * \brief Constructs a byte buffer from an integer number
     * \param integer number
     * \return the byte buffer
     */
    static ByteBuffer fromInt(int number)
    {
        char buffer [20];
        int nn = sprintf(buffer, "%d", number);

        if(nn > 0)
        {
            ByteBuffer bb = fromAscii(buffer, nn);
            return bb;
        }
        return ByteBuffer();
    }

    /**
     * \brief Constructs a integer from byte buffer
     * \return the integer number
     */
    int asInt() const
    {
        int i = 0;
        char buffer[20];
        this->asAscii(buffer,20);
        sscanf(buffer, "%d", &i);
        return i;
    }

private:

    /**
     * \brief Allocates the byte buffer of given length, but keeps the data uninitialized.
     * \param length the number of bytes to allocate
     */
    explicit ByteBuffer(size_t length) : m_length(length), m_data(m_length ? new uint8_t[m_length] : NULL)
    {
    }

    /**
     * \brief Deallocates the memory.
     */
    void clear()
    {
        if(m_data != NULL)
        {
            delete[] m_data;
            m_data = NULL;
            m_length = 0;
        }
    }

    size_t m_length;
    uint8_t *m_data;
};

static uint8_t hexDigitValue(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    if (c >= 'A' && c <= 'F')
    {
        return c - 'A' + 10;
    }
    if (c >= 'a' && c <= 'f')
    {
        return c - 'a' + 10;
    }
}

#endif // BYTEBUFFER_H
