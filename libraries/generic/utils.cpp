#include "utils.h"

Utils::Utils(){}
Utils::~Utils(){}

static double Utils::radToDeg(double rad)
{
    return rad*(180.0/PI);
}

static double Utils::degToRad(double deg)
{
    return deg*(PI/180);
}
