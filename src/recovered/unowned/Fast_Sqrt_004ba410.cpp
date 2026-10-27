#include "shared/fast_math.hpp"
union FastFloatBits { float Value; unsigned int Bits; };
float __cdecl Fast_Sqrt(double value)
{
    float absolute = (float)value;
    if (absolute == 0.0f) return 0.0f;
    if (absolute <= 0.0f) absolute *= -1.0;
    FastFloatBits number;
    number.Value = absolute;
    short exponent = (short)((number.Bits >> 23) - 127);
    unsigned int mantissa = number.Bits & 0x7fffff;
    if (exponent & 1) mantissa |= 0x800000;
    exponent >>= 1;
    FastFloatBits result;
    result.Bits = (exponent + 127) * 0x800000 + unknown_sqrt_table_817dfc[mantissa >> 10];
    return result.Value;
}
