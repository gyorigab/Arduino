#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include <Wire.h>

class Gyroscope
{
public:
    Gyroscope();
    ~Gyroscope();

    struct Angle
    {
        double X;
        double Y;

        Angle() : X(0.0), Y(0.0) {}
        ~Angle() {}
    };

    void init();
    Angle getAngle();

    double getTemperature();


private:

    void obtainRawData();

    Angle getAcclerationAngle();
    Angle getGyroscopeAngle();

    static const int ADDRESS  = 0x68;
    static const int PWR_MGMT_REGISTER = 0x6B;
    static const int ACCEL_XOUT_REGISTER = 0x3B;
    static const int TOTAL_REGISTERS = 14;

    int16_t m_accelerationX;
    int16_t m_accelerationY;
    int16_t m_accelerationZ;

    int16_t m_gyroscopeX;
    int16_t m_gyroscopeY;
    int16_t m_gyroscopeZ;

    int16_t m_temperature;

}

#endif
