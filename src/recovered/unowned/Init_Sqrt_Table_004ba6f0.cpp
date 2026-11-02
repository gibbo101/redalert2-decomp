// void Init_Sqrt_Table_004ba6f0() (0x004BA6F0)
// Builds the square-root mantissa table 0x00817DFC (TibSun fastmath.cpp
// init_sqrt_tab, the Graphics Gems III two-half build loop retargeted to
// float): the first half for an even exponent, the second for an odd one.
// @ref ?unknown_sqrt_table_817dfc@@=00817dfc
// @ref __real@4@0=0079a738
// @ref __real@8@bfff8000000000000000=0079d578
#include "shared/fast_math.hpp"


void Init_Sqrt_Table_004ba6f0()
{
    short i;
    float value;
    unsigned int *fi = (unsigned int *)&value;

    for (i = 0; i != 0x2000; i++) {
        value = 0;
        *fi = (i << 10) | (127 << 23);
        value = Fast_Sqrt(value);
        unknown_sqrt_table_817dfc[i] = *fi & 0x7fffff;

        value = 0;
        *fi = (i << 10) | (128 << 23);
        value = Fast_Sqrt(value);
        unknown_sqrt_table_817dfc[i + 0x2000] = *fi & 0x7fffff;
    }
}
