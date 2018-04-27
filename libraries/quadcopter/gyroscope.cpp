#include "gyroscope.h"
#include "utils.h"
#include "trace.h"

Gyroscope::Gyroscope()
{
    m_gyroscopeX = m_gyroscopeY = m_gyroscopeZ = 0;
    m_accelerationX = m_accelerationY = m_accelerationZ = 0;
    m_temperature = 0;

    m_totalAngle.setAngle(0.0,0.0);
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

    m_timer.init();
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
    TRACING(INF);

    double angleX = 0.0;
    double angleY = 0.0;

    // 1g = 16384.0 - defined by MPU6050
    const double gravity = 16384.0;

    // Acceleration in axes [g]
    double accX = double(m_accelerationX) / gravity;
    double accY = double(m_accelerationY) / gravity;
    double accZ = double(m_accelerationZ) / gravity;

    // Inclination angle of the IMU [rad]
    angleX = atan(accY / sqrt(pow(accX,2) + pow(accZ,2)));
    angleY = atan(-1 * accX / sqrt(pow(accY,2) + pow(accZ,2)));

    // Inclintation angle [deg]
    angleX = Utils::radToDeg(angleX);
    angleY = Utils::radToDeg(angleY);

    TRACE_VAR("Acceleration angle X: ", angleX, DBG);
    TRACE_VAR("Acceleration angle Y: ", angleY, DBG);
    TRACE_VAR("Acceleration angle Z: ", accZ   , DBG);

    return Angle(angleX, angleY);
}

Angle Gyroscope::getGyroscopeAngle()
{
    TRACING(INF);

    double angleX = 0.0;
    double angleY = 0.0;

    // Ratio defined by MPU6050
    const int ratio = 131.0;

    angleX = double(m_gyroscopeX) / ratio;
    angleY = double(m_gyroscopeY) / ratio;

    TRACE_VAR("Gyroscope angle X: ", angleX, DBG);
    TRACE_VAR("Gyroscope angle Y: ", angleY, DBG);

    return Angle(angleX, angleY);
}

Angle Gyroscope::getAngle()
{
    TRACING(INF);

    obtainRawData();

    // Get gyro and acc angle
    Angle accAngle = getAcclerationAngle();
    Angle gyrAngle = getGyroscopeAngle();

    // Elapsed time in seconds
    double elapsedTime = m_timer.getElapsedTime();

    TRACE_VAR("Elapsed time: ", elapsedTime,    DBG);
    TRACE_VAR("Prev angle X: ", m_totalAngle.getX(), DBG);
    TRACE_VAR("Prev angle Y: ", m_totalAngle.getY(), DBG);

    // Current angle is equal to previous obtained angle plus
    // angular velocity (degrees/second)
    m_totalAngle = m_totalAngle + gyrAngle * elapsedTime;

    // Total angle obtained from complementary filter
    m_totalAngle = complementaryFilter(m_totalAngle, accAngle);

    TRACE_VAR("Curr angle X: ", m_totalAngle.getX(), DBG);
    TRACE_VAR("Curr angle Y: ", m_totalAngle.getY(), DBG);

    return m_totalAngle;
}

double Gyroscope::getTemperature()
{
    obtainRawData();

    // Temperature in degrees of celsius
    return double(m_temperature) / 340.0 + 36.53;
}

Angle Gyroscope::complementaryFilter(const Angle &totalAngle, const Angle &accAngle )
{
    // low pass filter values
    const double highPass = 0.98;
    const double lowPass  = 0.02;

    // High-pass filtering of gyroscope. Low-pass filtering of accelerometer
    // 98% of gyro angle data and 2% of accelerometer angle data
    Angle angle = totalAngle * highPass + accAngle * lowPass;

    return angle;
}
