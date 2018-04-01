#ifndef JOYSTICK_H
#define JOYSTICK_H

#ifndef GDEBUG
#include <Arduino.h>
#endif

class Joystick final
{
public:

    struct Data
    {
        int upper;
        int lower;
        int left;
        int right;

        bool key;

        Data() : upper(0), lower(0), left(0), right(0), key(false) {}
    };

    Joystick(int pinX, int pinY, int pinKey);
    ~Joystick();

    Data getJoystickPosition();
    void init();

private:

    int m_pinX;
    int m_pinY;
    int m_pinKey;

    int m_zeroX;
    int m_zeroY;

    static const int MIN = 0;
    static const int MAX = 100;

};

#endif
