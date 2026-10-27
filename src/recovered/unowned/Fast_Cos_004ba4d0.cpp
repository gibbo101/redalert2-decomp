#include "shared/fast_math.hpp"
float __cdecl Fast_Cos(double angle)
{
    float value = (float)angle;
    int doubled = (int)(value * unknown_cos_scale_7d804c);
    bool round_up = (doubled & 1) != 0;
    int index = (doubled / 2) % 8192;
    if (index < 0) index += 10240;
    else index += 2048;
    if (round_up) {
        if (index < 10239) ++index;
    }
    double sample=unknown_sin_table_801dc4[index];
    return sample;
}

