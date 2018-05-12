#ifndef JOYSTICK_H
#define JOYSTICK_H

#ifndef GDEBUG
#include <Arduino.h>
#endif

class Joystick final
{
public:

    /**
    * \brief Data structure to store joystick data
    */
    struct Data
    {
        uint8_t upper;
        uint8_t lower;
        uint8_t left;
        uint8_t right;

        bool key;

        Data() : upper(0), lower(0), left(0), right(0), key(false) {}
    };

    /**
    * \brief Joystick constructor
    * \param Analog arduino pin e.g. A0, A1... of X axis data
    * \param Analog arduino pin e.g. A0, A1... of Y axis data
    * \param Analog arduino pin e.g. A0, A1... of joystick button
    */
    Joystick(uint8_t pinX, uint8_t pinY, uint8_t pinKey);
    ~Joystick();

    /**
    * \brief Joystick constructor
    * \return data of axes X and Y and button state
    */
    Data getJoystickPosition() const;


    /**
    * \brief Init Joystick HW. Set pins to arduino controler
    */
    void init();

private:

    int m_pinX;    // joystick analog pin of X axis
    int m_pinY;    // joystick analog pin of Y axis
    int m_pinKey;  // joystick button digital pin

    int m_zeroX;   // analog X axis value obtained in default position
    int m_zeroY;   // analog Y axis value obtained in default position

    static const int MIN = 0;
    static const int MAX = 254;
};

#endif
