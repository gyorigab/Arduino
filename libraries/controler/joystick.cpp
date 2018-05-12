#include "joystick.h"
#include "trace.h"

typedef Joystick::Data Data;

Joystick::Joystick(uint8_t pinX, uint8_t pinY, uint8_t pinKey)
{
    m_pinX   = pinX;
    m_pinY   = pinY;
    m_pinKey = pinKey;
}

Joystick::~Joystick()
{

}

void Joystick::init()
{
    pinMode(m_pinKey, INPUT_PULLUP);

    m_zeroX = analogRead(m_pinX);
    m_zeroY = analogRead(m_pinY);
}

Data Joystick::getJoystickPosition() const
{
    TRACE_FUNCTION();
    TRACING(INF);

    TRACE_VAR("Joystyck Zero X: ", m_zeroX, DBG);
    TRACE_VAR("Joystyck Zero Y: ", m_zeroY, DBG);

    Data d;

    int x =  analogRead(m_pinX) - m_zeroX;
    int y =  analogRead(m_pinY) - m_zeroY;

    TRACE_VAR("Joystick Analog RAW X: ", analogRead(m_pinX), DBG);
    TRACE_VAR("Joystick Analog RAW Y: ", analogRead(m_pinY), DBG);

    TRACE_VAR("Joystick Analog X: ", x, DBG);
    TRACE_VAR("Joystick Analog Y: ", y, DBG);

    if(x > 0) { d.upper = map(x, 0, 1023 - m_zeroX, MIN, MAX); }
    else      { d.lower = map(x, 0,      - m_zeroX, MIN, MAX); }

    if(y > 0) { d.right = map(y, 0, 1023 - m_zeroY, MIN, MAX); }
    else      { d.left  = map(y, 0,      - m_zeroY, MIN, MAX); }

    int keyPressed = digitalRead(m_pinKey);

    if(keyPressed == LOW)
    {
        d.key = true;
    }

    return d;
}
