// CoordStruct __fastcall Lerp(CoordStruct const &from, CoordStruct const &to, float t) (0x007220C0)
// The coordinate a fraction t of the way from from to to (TibSun Lerp).
#include "shared/wave.hpp"

CoordStruct __fastcall Lerp(CoordStruct const &from, CoordStruct const &to, float t)
{
    return CoordStruct((int)(to.X * t + from.X * (1.0 - t)), (int)(to.Y * t + from.Y * (1.0 - t)), (int)(to.Z * t + from.Z * (1.0 - t)));
}
