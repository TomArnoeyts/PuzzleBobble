#include "StdAngle.h"
float StdAngle::CalculateStdAngle(int Degrees)
{
    float result=0;

    if (Degrees > 270)
        result = ((float)(2*PI*(179-(Degrees-270))))/((float)360);
    else
        result = ((float)(2*PI*(90-Degrees)))/((float)360);
    return result;
}
