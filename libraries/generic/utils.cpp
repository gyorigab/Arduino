#include "utils.h"
#include "math.h"

Utils::Utils(){}
Utils::~Utils(){}

float Utils::radToDeg(float rad)
{
    return rad*(180.0/M_PI);
}

float Utils::degToRad(float deg)
{
    return deg*(M_PI/180.0);
}
