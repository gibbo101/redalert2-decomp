#include "shared/fast_math.hpp"
// The callee pops one 4-byte float argument. Original C++ declaration
// and non-stack calling-convention details remain unresolved.
union RootFloatBits { float Value; unsigned int Bits; };
// @ref ?unknown_sqrt_table_817dfc@@=00817dfc
// @ref __real@4@0=0079a738
// @ref __real@8@bfff8000000000000000=0079d578
float __stdcall Fast_Sqrt_Float_004BA830(float value)
{
    if (value == 0.0f) return 0.0f;
    float absolute = value <= 0.0f ? value * -1.0 : value;
    RootFloatBits &number = *(RootFloatBits *)&absolute;
    short exponent = (short)((number.Bits >> 23) - 127);
    unsigned int mantissa = number.Bits & 0x7fffff;
    if (exponent & 1) mantissa |= 0x800000;
    exponent >>= 1;
    number.Bits = (exponent + 127) * 0x800000 + unknown_sqrt_table_817dfc[mantissa >> 10];
    return absolute;
}