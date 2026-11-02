// float Fast_Sqrt(double value) (0x004BA410)
// The double face of the table square root (TibSun fastmath::sqrt): no more
// precision than the float function it expands.
#include "shared/fast_math.hpp"

float __cdecl Fast_Sqrt(double value)
{
    return (float)Fast_Sqrt_Float_004BA830((float)value);
}
