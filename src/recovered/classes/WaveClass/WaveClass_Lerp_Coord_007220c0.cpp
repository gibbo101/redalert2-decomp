// CoordStruct __fastcall Lerp(CoordStruct const &from, CoordStruct const &to, float t) (0x007220C0)
// The coordinate a fraction t of the way from from to to (TibSun Lerp). The result is built as
// UnknownCoord434820 (TibSun's Coord): where Wave_Recalc_Affected_Cells expands Lerp, that
// constructor stays out of line (0x00434820) as in the original.
#include "shared/wave.hpp"

CoordStruct __fastcall Lerp(CoordStruct const &from, CoordStruct const &to, float t)
{
    return UnknownCoord434820((int)(to.X * t + from.X * (1.0 - t)), (int)(to.Y * t + from.Y * (1.0 - t)), (int)(to.Z * t + from.Z * (1.0 - t)));
}
