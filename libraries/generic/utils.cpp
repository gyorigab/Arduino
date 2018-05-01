#include "utils.h"
#include "math.h"

Utils::Utils(){}
Utils::~Utils(){}

double Utils::radToDeg(double rad)
{
    return rad*(180.0/M_PI);
}

double Utils::degToRad(double deg)
{
    return deg*(M_PI/180.0);
}
