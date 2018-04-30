#include "utils.h"

Utils::Utils(){}
Utils::~Utils(){}

double Utils::radToDeg(double rad)
{
    return rad*(180.0/PI);
}

double Utils::degToRad(double deg)
{
    return deg*(PI/180);
}
