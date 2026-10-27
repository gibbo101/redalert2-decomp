// Vector3 __fastcall unknown_scaled_vector(int index, int arg2) -- 0x00718FA0
// Purpose: entry `index` of the vector table at 0x00AF6768, scaled by
// 1.5 (each component through a float temporary). arg2 is unused.
// Assumptions: what the table holds is unknown.
#include "shared/vector3.hpp"
// @ref ?unknown_vectors_af6768@@3PAUVector3@@A=00af6768
// @ref __real@4@3fffc000000000000000=0079d0e8

extern Vector3 unknown_vectors_af6768[];

Vector3 __fastcall unknown_scaled_vector(int index, int arg2)
{
    Vector3 &entry = unknown_vectors_af6768[index];
    return Vector3(entry.X * 1.5f, entry.Y * 1.5f, entry.Z * 1.5f);
}
