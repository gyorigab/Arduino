#ifndef JOYSTICKDATA_H
#define JOYSTICKDATA_H

class JoystickData
{
public:

    JoystickData() :
        m_upper(0), m_lower(0), m_left(0), m_right(0)
    {

    }

    JoystickData(int upper, int lower, int left, int right) :
        m_upper(upper), m_lower(lower), m_left(left), m_right(right)
    {

    }

    int getUpper() {return m_upper;}
    int getLower() {return m_lower;}
    int getLeft()  {return m_left;}
    int getRight() {return m_right;}

private:
    int m_upper;
    int m_lower;
    int m_left;
    int m_right;
};

#endif
