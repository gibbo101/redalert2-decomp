// CoordStruct *__fastcall Unknown_007220C0(CoordStruct *result, CoordStruct const &b, CoordStruct const &a, float amount) (0x007220C0)
// The point between two coordinates: a * amount + b * (1 - amount), per axis.
#include "shared/wave.hpp"

CoordStruct *__fastcall Unknown_007220C0(CoordStruct *result, CoordStruct const &b, CoordStruct const &a, float amount)
{
    *result = CoordStruct((int)(a.X * amount + b.X * (1.0 - amount)), (int)(a.Y * amount + b.Y * (1.0 - amount)), (int)(a.Z * amount + b.Z * (1.0 - amount)));
    return result;
}
