#include "joystick.h"
#include "trace.h"

typedef Joystick::Data Data;

Joystick::Joystick(int pinX, int pinY, int pinKey)
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
    Trace::print("Joystick init()");

    pinMode(m_pinKey, INPUT_PULLUP);

    m_zeroX = analogRead(m_pinX);
    m_zeroY = analogRead(m_pinY);
}

Data Joystick::getJoystickPosition()
{
    TRACE_FUNCTION();

    Data d;

    int x =  analogRead(m_pinX) - m_zeroX;
    int y =  analogRead(m_pinY) - m_zeroY;

    if(x > 0) { d.upper = map(x, 0, 1023 - m_zeroX, MIN, MAX); }
    else      { d.lower = map(x, 0,      - m_zeroX, MIN, MAX); }

    if(y > 0) { d.left  = map(y, 0, 1023 - m_zeroY, MIN, MAX); }
    else      { d.right = map(y, 0,      - m_zeroY, MIN, MAX); }

    int keyPressed = digitalRead(m_pinKey);

    if(keyPressed == LOW)
    {
        d.key = true;
    }

    return d;
}
