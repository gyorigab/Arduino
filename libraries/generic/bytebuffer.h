#ifndef BYTEBUFFER_H
#define BYTEBUFFER_H

#ifdef GDEBUG
#include <stdint.h>
#include <cstddef>
#include <stdio.h>
#include <cstring>
#include <iostream>
#endif

/**
 * \brief An array of bytes.
 *
 * The data is allocated on the stack or on the heap. Each instance makes its own copy of the data in constructor.
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
     * \brief Allocates the byte buffer of given length, but keeps the data uninitialized.
     * \param length the number of bytes to allocate
     */
    ByteBuffer(size_t capacity = 32) : m_length(0)
    {
        if(capacity > m_internalCapacity)
        {   
            m_externalCapacity = capacity;
            m_data = new uint8_t[m_externalCapacity];
            m_isExternalBufferUsed = true;
        }
        else
        {
            m_externalCapacity = 0;
            m_data = NULL;
            m_isExternalBufferUsed = false;
            memset(m_internalData, 0, m_internalCapacity);
        }
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
        m_length = length;

        if (m_isExternalBufferUsed)
        {
            copy(src, m_data, length);
        }
        else
        {
            copy(src, &m_internalData[0], length);
        }
    }

    size_t copy(const uint8_t *src, uint8_t *dst, size_t len)
    {
        size_t dataCopied = 0;

        if(len > 0 && src != NULL)
        {
            for( ; dataCopied < m_length; dataCopied++)
            {
                dst[dataCopied] = src[dataCopied];
            }
        }

        return dataCopied;
    }

    /**
     * \brief Assigment operator overloading
     */
    ByteBuffer &operator=(const ByteBuffer &src)
    {
        if (&src != this)
        {
            m_length = src.m_length;
            m_externalCapacity = src.m_externalCapacity;
            m_isExternalBufferUsed = src.m_isExternalBufferUsed;
            
            if (m_isExternalBufferUsed)
            {
                delete[] m_data;
                m_data = new uint8_t[m_externalCapacity];
                copy(src.m_data, m_data, m_length);
            }
            else
            {
                m_data = NULL;
                memset(m_internalData, 0, m_internalCapacity);
                copy(&src.m_internalData[0], &m_internalData[0],m_length); 
            }
        }

        return *this;
    }

    /**
     * \brief Copy constructor
     */
    ByteBuffer(const ByteBuffer &src)
    {
        m_length = src.m_length;
        m_externalCapacity = src.m_externalCapacity;
        m_isExternalBufferUsed = src.m_isExternalBufferUsed;
        
        if (m_isExternalBufferUsed)
        {
            m_data = new uint8_t[m_externalCapacity];
            copy(src.m_data, m_data, m_length);
        }
        else
        {
            m_data = NULL;
            memset(m_internalData, 0, m_internalCapacity);
            copy(&src.m_internalData[0], &m_internalData[0], m_length);
        }
    }

    /**
     * \brief Overloading of equality operator for comparison content of two byte arrays
     * \return true if all items of both buffers are equal
     */
    bool operator==(const ByteBuffer& buff)
    {
        if(m_length != buff.m_length || m_isExternalBufferUsed != buff.m_isExternalBufferUsed)
        {
            return false;
        }
        
        if(m_isExternalBufferUsed)
        {
            return areEqual(m_data, buff.m_data);
        }
        else
        {
            return areEqual(&m_internalData[0], &buff.m_internalData[0]);
        }
    }

    // TODO will be private
    bool areEqual(const uint8_t *data, const uint8_t *inputData)
    {
        for(int i = 0; i < m_length; i++)
        {
           if(data[i] != inputData[i])
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
        if(m_isExternalBufferUsed)
        {
            return m_data;
        }
        else
        {
            return &m_internalData[0];
        }
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
         if (m_isExternalBufferUsed)
         {
             return get(index, m_data);
         }
         else
         {
             return get(index, &m_internalData[0]);
         }
    }

    // TODO will be private
    uint8_t get(size_t index, const uint8_t *data) const
    {
        if (index >= 0 && index < m_length)
        {
            return data[index];
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
            size_t length = end - start;

            ByteBuffer bb(length);
            bb.m_length = length;

            if (length > 0)
            {
                if(bb.m_isExternalBufferUsed && m_isExternalBufferUsed)
                {
                    for(size_t i = start, j = 0; j < length; i++, j++)
                    {
                        bb.m_data[j] = m_data[i];
                    }
                }
                else if(!bb.m_isExternalBufferUsed && !m_isExternalBufferUsed)
                {
                    for(size_t i = start, j = 0; j < length; i++, j++)
                    {
                        bb.m_internalData[j] = m_internalData[i];
                    }
                }
                else
                {
                    for(size_t i = start, j = 0; j < length; i++, j++)
                    {
                        bb.m_internalData[j] = m_data[i];
                    }
                }
            }
            return bb;
        }
        else
        {
            return ByteBuffer(0);
        }
    }

    /**
    * \brief Append a new value to the content of this byte buffer.
    * \param  bytes to append
    * \param  length of the byte array
    * \return the new byte buffer
    */
    ByteBuffer& append(const uint8_t *src, size_t length)
    {
        if (m_isExternalBufferUsed)
        {
            //check if there is enough of space
            if(m_length + length > m_externalCapacity)
            {
                realocate(length);
            }

            // External buffer is used. Append data to external buffer
            for(int i = 0; i < length; i++)
            {
                m_data[m_length++] = src[i];
            }
        }
        else
        {
            if(m_length + length > m_internalCapacity)
            {
                realocate(length);

                // Internal buffer was used but append operation caused realocation
                // Realocation moved internal buffer to external buffer 
                // Append data to external buffer
                for(int i = 0; i < length; i++)
                {
                    m_data[m_length++] = src[i];
                }
            }
            else
            { 
                 // Internal buffer was used no realocation was needed
                 // Append data to internla buffer
                 for(int i = 0; i < length; i++)
                 {
                      m_internalData[m_length++] = src[i];
                 }
            }
        }

        return *this;
    }

    /**
     * \brief Creates a new byte buffer by appending another byte buffer to the content of this byte buffer.
     * \param buf the byte buffer to append
     * \return the new byte buffer
     */
    ByteBuffer append(const ByteBuffer &buf)
    {
        if(m_isExternalBufferUsed)
        {
            return append(buf.m_data, buf.m_length);
        }
        else
        {
            return append(&buf.m_internalData[0], buf.m_length);
        }
    }

    /**
     * \brief Creates a new byte buffer by appending a byte to the content of this byte buffer.
     * \param value the byte to append
     * \return the new byte buffer
     */
    ByteBuffer appendUint8(uint8_t value)
    {
        return append(&value, 1);
    }
    /**
     * \brief Creates a new byte buffer by appending a little endian encoding of a 16-bit unsigned value
     * to the content of this byte buffer.
     * \param value the value to append
     * \return the new byte buffer
     */
    ByteBuffer appendUint16LE(uint16_t value)
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
    ByteBuffer appendUint16BE(uint16_t value)
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
            return ByteBuffer(0);
        }

        ByteBuffer bb(len / 2);
        bb.m_length = len / 2;

        if(bb.m_isExternalBufferUsed)
        {
            fromHex(hex, bb.m_data, bb.m_length);
        }
        else
        {
            fromHex(hex, &bb.m_internalData[0], bb.m_length);
        }

        return bb;
    }

    static void fromHex(const char* hex, uint8_t *dst, size_t len)
    {
        for (size_t i = 0; i < len; ++i)
        {
            dst[i] = (hexDigitValue(hex[2 * i]) << 4) | hexDigitValue(hex[2 * i + 1]);
        }
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
        bb.m_length = len;

        bool res = false;

        if(bb.m_isExternalBufferUsed)
        {
             res = fromAscii(ascii, bb.m_data, len);
        }
        else
        {
            res = fromAscii(ascii, &bb.m_internalData[0], len);
        }

        if(res)
            return bb;
        else
            return ByteBuffer(0);
    }

    // TODO will be private
    static bool fromAscii(const char* ascii, uint8_t *dst, size_t len)
    {
        for (size_t i = 0; i < len; ++i)
        {
            char c = ascii[i];
            if (c < 0 || c > 127)
            {
                return false;
            }
            dst[i] = c;
        }
        return true;
    }

    /**
     * \brief Returns an ASCII string made from the bytes in the buffer.
     * \return an ASCII string
     * \throws Exception if the buffer contains bytes outside of the ASCII charset (>= 128)
     */
    void asAscii(char* string, size_t len) const
    {
        if(m_length > len-1)
        {
            return;
        }

        if(m_isExternalBufferUsed)
        {
             asAscii(m_data, string);
        }
        else
        {
             asAscii(&m_internalData[0], string);
        }
    }

    //TODO will be private
    void asAscii(const uint8_t *src, char *dst) const
    {
        for (size_t i = 0; i < m_length; i++)
        {
            if (src[i] > 127)
            {
                return;
            }
            dst[i] = static_cast<char>(src[i]);
        }

        // zero terminated string
        dst[m_length] = 0;
    }

    /**
     * \brief Constructs a byte buffer from an integer number
     * \param integer number
     * \return the byte buffer
     */
    static ByteBuffer fromInt(int number, uint8_t digits = 20)
    {
        char buffer [digits];
        int nn = sprintf(buffer, "%d", number);

        if(nn > 0)
        {
            ByteBuffer bb = fromAscii(buffer, nn);
            return bb;
        }

        return ByteBuffer(0);
    }

    /**
     * \brief Constructs a integer from byte buffer
     * \return the integer number
     */
    int asInt(uint8_t digits = 20) const
    {
        int i = 0;
        char buffer[digits];
        this->asAscii(buffer,digits);
        //TODO nahradit za strtol
        sscanf(buffer, "%d", &i);
        return i;
    }

    static ByteBuffer fromInt8(int number)
    {
        return fromInt(number, 4);
    }

    int asInt8() const
    {
        return asInt(4);
    }

    /**
     * \brief Deallocates the memory.
     */
    void clear()
    {
        if(!m_isExternalBufferUsed)
        {
            memset(m_internalData, 0, m_internalCapacity);
            m_length = 0;
        }

        if(m_data != NULL)
        {
            delete[] m_data;
            m_data = NULL;
            m_length = 0;
            m_externalCapacity = 0;
        }
    }

private:

    void realocate(size_t length = 0)
    {
        ByteBuffer tmp = *this;
        clear();

        m_length = tmp.m_length;

        if(m_isExternalBufferUsed)
        {
            m_externalCapacity = tmp.m_externalCapacity + length + 8;
        }
        else
        {
            m_externalCapacity = tmp.m_internalCapacity + length + 8;
        }

        m_data = m_externalCapacity ? new uint8_t[m_externalCapacity] : NULL;

        if(m_isExternalBufferUsed)
        {
            for(int i = 0; i < m_length; i++)
            {
                m_data[i] = tmp.m_data[i];
            }
        }
        else
        {
            for(int i = 0; i < m_length; i++)
            {
                m_data[i] = tmp.m_internalData[i];
                m_internalData[i] = 0;
            }
        }
    }


    size_t m_length;
    size_t m_externalCapacity;
    uint8_t *m_data;

    static const size_t m_internalCapacity = 32;
    uint8_t m_internalData[m_internalCapacity];
    bool m_isExternalBufferUsed;
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
