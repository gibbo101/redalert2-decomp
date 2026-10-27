#include "shared/fast_math.hpp"
float __cdecl Fast_Sin(double angle)
{
    float value = (float)angle;
    int doubled = (int)(value * unknown_sin_scale_7d8048);
    bool round_up = (doubled & 1) != 0;
    int index = (doubled / 2) % 8192;
    if (index < 0) index += 8192;
    if (round_up) {
        if (index < 8191) ++index;
    }
    double sample=unknown_sin_table_801dc4[index];
    return sample;
}

