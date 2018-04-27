#include "angle.h"

Angle operator+(const Angle &a, const Angle &b)
{
    return Angle(a.m_X + b.m_X, a.m_Y + b.m_Y);
}

Angle operator*(const Angle &a, double b)
{
    return Angle(a.m_X * b, a.m_Y * b);
}

Angle operator*(double b, const Angle &a)
{
    return a * b ;
}

Angle operator-(const Angle &a, const Angle &b)
{
    return Angle(a.m_X - b.m_X, a.m_Y - b.m_Y);
}

Angle operator/(const Angle &a, double b)
{
    if(b != 0)
    {
        return Angle(a.m_X / b, a.m_Y / b);
    }
    else
    {
        return Angle();
    }
}
