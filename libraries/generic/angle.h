#ifndef ANGLE_H
#define ANGLE_H

#include "utils.h"

class Angle
{
public:

    enum Units{DEG, RAD};

    Angle() : m_X(0.0), m_Y(0.0), m_unit(DEG) {}
    Angle(double X, double Y, Units unit = DEG) : m_X(X), m_Y(Y) {}

    ~Angle() {}

    double getX(){return m_X;}
    double getY(){return m_Y;}

    void setX(double X){m_X = X;}
    void setY(double Y){m_Y = Y;}
    void setUnit(Units u){m_unit = u;}

    void setAngle(double X, double Y)
    {
        m_X = X;
        m_Y = Y;
    }

    // TODO doimplementovat
    void toDeg(){}
    void toRad(){}

private:
    double m_X;
    double m_Y;

    Units m_unit;

};

#endif
