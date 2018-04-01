#ifndef HASHMAP_H
#define HASHMAP_H

#include "trace.h"

class HashMap final
{
public:
    struct Record
    {
        ByteBuffer m_key;
        ByteBuffer m_value;

        Record() : m_key(ByteBuffer()), m_value(ByteBuffer()){}
        Record(ByteBuffer key, ByteBuffer value) : m_key(key), m_value(value){}

        Record &operator=(const Record &src)
        {
            if (&src != this)
            {
                m_key = src.m_key;
                m_value = src.m_value;
            }
            return *this;
        }

        Record(const Record &src)
        {
            m_key = src.m_key;
            m_value = src.m_value;
        }
    };

    HashMap(size_t capacity = 16) : m_capacity(capacity), m_size(0)
    {
        Trace::print("Hash map constructor - begin");
        m_records =  m_capacity ? new Record[m_capacity] : NULL;
        Trace::print("Hash map constructor - end");
    }

    ~HashMap()
    {
        clear();
    }

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

    ByteBuffer operator[](const ByteBuffer &key) const
    {
        return getValue(key);
    }

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

    ByteBuffer getValue(size_t index) const
    {
        if( index < m_size )
        {
            return m_records[index].m_value;
        }
        return ByteBuffer();
    }

    ByteBuffer getKey(size_t index) const
    {
        if( index < m_size )
        {
            return m_records[index].m_key;
        }
        return ByteBuffer();
    }

    size_t size() const
    {
        return m_size;
    }

    size_t capacity() const
    {
        return m_capacity;
    }

    bool empty() const
    {
        return m_size > 0 ? false : true;
    }

    bool full() const
    {
        return !(m_size < m_capacity);
    }

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
