// ?Fast_Atan@@YAMN@Z (0x004BA5B0)
// Arctangent from the 0x1001-entry table (pi/2 beyond it), sign from value.
#include "shared/crt_memory.hpp"
#include "shared/fast_math.hpp"
// @ref __real@4@3fffc90fdb0000000000=007a0f8c
// @ref ?unknown_atan_step_817df8@@3MA=00817df8
// @ref ?unknown_atan_table_813df4@@3PAMA=00813df4

float __cdecl Fast_Atan(double value)
{
    float number = (float)value;
    int index = abs((int)(number / unknown_atan_step_817df8));
    float result;
    if (index < 0x1001) {
        result = unknown_atan_table_813df4[index];
    } else {
        result = 1.5707964f;
    }
    if (number < 0.0f) {
        result = -result;
    }
    return result;
}
