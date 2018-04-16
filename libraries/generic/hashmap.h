#ifndef HASHMAP_H
#define HASHMAP_H

#include "trace.h"

class HashMap final
{
public:

    /**
    * \brief Key-value pair of one hashmap array record
    */
    struct Record
    {
        ByteBuffer m_key;
        ByteBuffer m_value;

        Record() : m_key(ByteBuffer()), m_value(ByteBuffer()){}
        Record(ByteBuffer key, ByteBuffer value) : m_key(key), m_value(value){}

        /**
        * \brief Assigment operator overloading
        */
        Record &operator=(const Record &src)
        {
            if (&src != this)
            {
                m_key = src.m_key;
                m_value = src.m_value;
            }
            return *this;
        }

        /**
        * \brief Copy constructor
        */
        Record(const Record &src)
        {
            m_key = src.m_key;
            m_value = src.m_value;
        }
    };

    /**
    * \brief Build hash map array (implicit count of records are 16)
    */
    HashMap(size_t capacity = 16) : m_capacity(capacity), m_size(0)
    {
        TRACING(INF);
        TRACE("Hash map constructor - begin", DBG);
        m_records =  m_capacity ? new Record[m_capacity] : NULL;
    }

    ~HashMap()
    {
        clear();
    }

    /**
    * \brief Assigment operator overloading
    */
    HashMap &operator=(const HashMap &src)
    {
        if (&src != this)
        {
            delete[] m_records;

            m_size = src.m_size;
            m_capacity = src.m_capacity;
            m_records = m_capacity ? new Record[m_capacity] : NULL;

            for(int i = 0; i < m_size; i++)
            {
                m_records[i] = src.m_records[i];
            }
        }

        return *this;
    }

    /**
    * \brief Copy constructor
    */
    HashMap(const HashMap &src)
    {
        m_size = src.m_size;
        m_capacity = src.m_capacity;
        m_records = m_capacity ? new Record[m_capacity] : NULL;

        for(int i = 0; i < m_size; i++)
        {
            m_records[i] = src.m_records[i];
        }
    }

    /**
    * \brief Get value of given key (operator overload)
    *
    * \param byte stream which represents key
    * \return byte stream data of given key
    */
    ByteBuffer operator[](const ByteBuffer &key) const
    {
        return getValue(key);
    }

    /**
    * \brief Insert pair of data key-value
    *
    * \param byte stream of key
    * \param byte stream of data
    * \return ture if record was successfuly inserted
    */
    bool insert(const ByteBuffer &key, const ByteBuffer &value)
    {
        if(!full() && !exists(key))
        {
            m_records[m_size] = Record(key, value);
            m_size++;
            return true;
        }
        return false;
    }

    /**
    * \brief Check if given key exists in current hasmap array
    *
    * \param byte stream of key
    * \return ture if key exists
    */
    bool exists(const ByteBuffer &key) const
    {
        for(int i = 0; i < m_size; i++)
        {
            if(m_records[i].m_key == key)
            {
                return true;
            }
        }
        return false;
    }

    /**
    * \brief Get value of given key
    *
    * \param byte stream which represents key
    * \return byte stream data of given key
    */
    ByteBuffer getValue(const ByteBuffer &key) const
    {
        for(int i=0; i < m_size; i++)
        {
            if(m_records[i].m_key == key)
            {
                return m_records[i].m_value;
            }
        }
        return ByteBuffer();
    }

    /**
    * \brief Get value of given index
    *
    * \param index of the hashmap array (0..size-1)
    * \return data of given index
    */
    ByteBuffer getValue(size_t index) const
    {
        if( index < m_size )
        {
            return m_records[index].m_value;
        }
        return ByteBuffer();
    }

    /**
    * \brief Get key of given index
    *
    * \param index of the hashmap array (0..size-1)
    * \return key of given index
    */
    ByteBuffer getKey(size_t index) const
    {
        if( index < m_size )
        {
            return m_records[index].m_key;
        }
        return ByteBuffer();
    }

    /**
    * \brief Get size of current hashmap array
    *
    * \return actual size of hashmap array
    */
    size_t size() const
    {
        return m_size;
    }


    /**
    * \brief Get capacity of current hashmap array
    *
    * \return actual capacity of hashmap array
    */
    size_t capacity() const
    {
        return m_capacity;
    }

    /**
    * \brief Check if current hashmap array is empty
    *
    * \return true if it is empty
    */
    bool empty() const
    {
        return m_size > 0 ? false : true;
    }


    /**
    * \brief Check if current hashmap array is full
    *
    * \return true if it is full
    */
    bool full() const
    {
        return !(m_size < m_capacity);
    }

    /**
    * \brief Clear current hashmap array

    */
    void clear()
    {
        if(m_records != NULL)
        {
            delete[] m_records;
            m_capacity = 0;
            m_size = 0;
            m_records = NULL;
        }
    }

private:
    Record *m_records;
    size_t m_capacity;
    size_t m_size;
};

#endif
