#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
    Timer();
    ~Timer();

    void init();

    /**
    * \brief Function compute elapsed time between two last call of this function
    *
    * \return elpased time in [s]
    */
    double getElapsedTime();

private:

    double m_previousTime;
};

#endif
