#include "gyroscope.h"
#include "utils.h"

typedef Gyroscope::Angle Angle;

Gyroscope::Gyroscope()
{
    m_gyroscopeX = m_gyroscopeY = m_gyroscopeZ = 0;
    m_accelerationX = m_accelerationY = m_accelerationZ = 0;
    m_temperature = 0;
}

Gyroscope::~Gyroscope()
{
}

void Gyroscope::init()
{
    Wire.begin();
    Wire.beginTransmission(ADDRESS);
    Wire.write(PWR_MGMT_REGISTER);
    Wire.write(0);
    Wire.endTransmission(true);
}

void Gyroscope::obtainRawData()
{
    Wire.beginTransmission(ADDRESS);
    Wire.write(ACCEL_XOUT_REGISTER);
    Wire.endTransmission(false);
    Wire.requestFrom(ADDRESS,TOTAL_REGISTERS,true);

    m_gyroscopeX = m_gyroscopeY = m_gyroscopeZ = 0;
    m_accelerationX = m_accelerationY = m_accelerationZ = 0;
    m_temperature = 0;

    m_accelerationX = Wire.read() << 8 | Wire.read();
    m_accelerationY = Wire.read() << 8 | Wire.read();
    m_accelerationZ = Wire.read() << 8 | Wire.read();
    m_temperature   = Wire.read() << 8 | Wire.read();
    m_gyroscopeX    = Wire.read() << 8 | Wire.read();
    m_gyroscopeY    = Wire.read() << 8 | Wire.read();
    m_gyroscopeZ    = Wire.read() << 8 | Wire.read();
}

Angle Gyroscope::getAcclerationAngle()
{
    Angle angle;
    const double sensitivity = 16384.0;

    double accX = double(m_accelerationX) / sensitivity;
    double accY = double(m_accelerationY) / sensitivity;
    double accZ = double(m_accelerationZ) / sensitivity;

    angle.X = atan(accY / sqrt(pow(accX,2) + pow(accZ,2)));
    angle.Y = atan(-1 * accX / sqrt(pow(accY,2) + pow(accZ,2)));

    // convert radians to degrees
    angle.X = Utils::radToDeg(angle.X);
    angle.Y = Utils::radToDeg(angle.Y);

    return angle;
}

Angle Gyroscope::getGyroscopeAngle()
{
    Angle angle;

    const int ratio = 131.0;

    angle.X = double(m_gyroscopeX) / ratio;
    angle.Y = double(m_gyroscopeY) / ratio;

    return angle;
}

Angle Gyroscope::getAngle()
{
    Angle angle;
    obtainRawData();

    return angle;
}

double Gyroscope::getTemperature()
{
    obtainRawData();

    // Temperature in degrees of celsius
    return double(m_temperature) / 340.0 + 36.53;
}


