// ?Fast_Atan2@@YAMNN@Z (0x004BA600)
// Arctangent of y / x over the full circle (0 for the origin).
#include "shared/crt_memory.hpp"
#include "shared/fast_math.hpp"
// @ref __real@4@3fffc90fdb0000000000=007a0f8c
// @ref __real@4@bfffc90fdb0000000000=007a0f90
// @ref __real@8@4000c90fdaa22168c000=0079d158
// @ref ?unknown_atan_step_817df8@@3MA=00817df8
// @ref ?unknown_atan_table_813df4@@3PAMA=00813df4

float __cdecl Fast_Atan2(double y, double x)
{
    float fx = (float)x;
    float fy = (float)y;
    if (fx == 0.0f) {
        if (fy == 0.0f) {
            return 0.0f;
        }
        if (fy > 0.0f) {
            return 1.5707964f;
        }
        return -1.5707964f;
    }
    int index = abs((int)(fy / fx / unknown_atan_step_817df8));
    float result;
    if (index < 0x1001) {
        result = unknown_atan_table_813df4[index];
    } else {
        result = 1.5707964f;
    }
    if (fx < 0.0f) {
        result = (float)(3.141592653589793 - result);
    }
    if (fy < 0.0f) {
        result = -result;
    }
    return result;
}
