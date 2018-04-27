#ifndef PID_H
#define PID_H

class Pid
{
public:
    struct Data
    {
        int upper;
        int lower;
        int left;
        int right;

        Data() : upper(0), lower(0), left(0), right(0) {}
    };

    Pid();
    ~Pid();

    void init();

private:
    double m_kp;
    double m_ki;
    double m_kd;

    double m_p;
    double m_i;
    double m_d;

};

#endif
