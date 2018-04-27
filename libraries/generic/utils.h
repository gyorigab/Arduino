#ifndef UTILS_H
#define UTILS_H

class Utils
{
public:
    Utils();
    ~Utils();

    static double radToDeg(double rad);
    static double degToRad(double deg);

private:

    static const double PI = 3.1415926;

};

#endif
