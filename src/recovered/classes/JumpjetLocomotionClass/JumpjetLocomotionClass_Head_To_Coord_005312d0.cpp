// CoordStruct __stdcall JumpjetLocomotionClass::Head_To_Coord() (0x005312D0, ILocomotion 6)
// The object's own coordinate while idle (+0x4C 0), otherwise the target
// coordinate (+0x3C).
#include "shared/jumpjet_locomotion.hpp"

CoordStruct __stdcall JumpjetLocomotionClass::Head_To_Coord()
{
    if (unknown_4c == 0) {
        CoordStruct coord = LinkedTo->Coord;
        return coord;
    }
    return CoordStruct(unknown_3c.X, unknown_3c.Y, unknown_3c.Z);
}
