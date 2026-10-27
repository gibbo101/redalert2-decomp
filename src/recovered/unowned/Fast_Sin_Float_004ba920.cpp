// @ref ?unknown_sin_scale_7d8048@@=007d8048
// @ref ?unknown_cos_scale_7d804c@@=007d804c
// @ref ?unknown_sin_table_801dc4@@=00801dc4
// @ref ?unknown_sin_table_80fde4@@=0080fde4
#include "shared/fast_math.hpp"
inline int Nearest_Trig_Index(int doubled_index, int quarter_offset)
{
    bool round_up = (doubled_index & 1) != 0;
    int index = (doubled_index / 2) % 8192;
    if(index<0) index+=8192+quarter_offset;
    else index+=quarter_offset;
    if (round_up) {
        if (index < 8191 + quarter_offset) index++;
    }
    return index;
}

// @ref __real@4@3fff8000000000000000=0079b7f8
// @ref __real@4@c00a8000000000000000=007a0f88
// @ref __real@8@3fffc90fdaa22168c000=0079b630
// @ref ?unknown_acos_table_80bdd4@@=0080bdd4
float __fastcall Fast_Sin_Float_004ba920(float angle)
{
    return unknown_sin_table_801dc4[Nearest_Trig_Index((int)(angle * unknown_sin_scale_7d8048), 0)];
}
