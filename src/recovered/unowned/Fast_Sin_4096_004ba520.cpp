#include "shared/fast_math.hpp"
// @ref __real@8@4008a2f9836e4e441800=007a0f80
float __cdecl Fast_Sin_4096(double angle)
{
    int index=(int)(angle*651.8986469044033)%4096;
    if(index<0) index+=4096;
    double sample=unknown_sin_table_80fde4[index];
    return sample;
}
