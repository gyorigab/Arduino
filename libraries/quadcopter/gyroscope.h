#ifndef GYROSCOPE_H
#define GYROSCOPE_H

#include <Wire.h>
#include <math.h>
#include "timer.h"
#include "angle.h"

class Gyroscope
{
public:
    Gyroscope();
    ~Gyroscope();

    /**
    * \brief Initialize gyroscope object, open reading and writing register
    */
    void init();

    /**
    * \brief Function computes angle from gyroscope and accelerometer data
    *
    * \return total filtered angle in [°]
    */
    Angle getAngle();

    /**
    * \brief Function computes temperature
    *
    * \return temperature [°C]
    */
    double getTemperature();

private:

    /**
    * \brief Function fills all sensor data in
    */
    void obtainRawData();

    /**
    * \brief Function computes angle from acceleration data by using Euler formula
    *
    * \return angle in [°]
    */
    Angle getAcclerationAngle();

    /**
    * \brief Function computes angle from gyroscope data
    *
    * \return angle in [°]
    */
    Angle getGyroscopeAngle();

    /**
    * \brief Angular data filter
    *
    * \param angle for High-pass filter
    * \param angle for Low-pass filter
    * \return angle in [°]
    */
    Angle complementaryFilter(const Angle &prevAngle, const Angle &accAngle );

    static const int ADDRESS  = 0x68;
    static const int PWR_MGMT_REGISTER = 0x6B;
    static const int ACCEL_XOUT_REGISTER = 0x3B;
    static const int TOTAL_REGISTERS = 6;

    // Center Gyroscope. HW position on drone is not perfectly horizontal.
    static const int16_t CENTER_CORRECTION_X =  2.80;
    static const int16_t CENTER_CORRECTION_Y = -9.10;


    int16_t m_accelerationX;
    int16_t m_accelerationY;
    int16_t m_accelerationZ;

    int16_t m_gyroscopeX;
    int16_t m_gyroscopeY;
    int16_t m_gyroscopeZ;

    int16_t m_temperature;

    Angle m_totalAngle;
    Timer m_timer;
};

#endif
