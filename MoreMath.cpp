#include "MoreMath.h"
#include <algorithm>


int MoreMath::sign(double value)
{
    return (value > 0) - (value < 0);
}

double MoreMath::clamp(double value, double min, double max)
{
    return std::min(std::max(value, min), max);
}
