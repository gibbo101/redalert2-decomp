// CoordStruct BuildingClass::unknown_slot44(int arg1) (0x0044A9A0, slot 44)
// The coordinate offset by the type's +0xC54 offset when it is not zero,
// otherwise the center.
#include "shared/building.hpp"
#include "shared/unknown_geometry.hpp"

static inline bool Coord_Differs(CoordStruct const &a, CoordStruct const &b)
{
    return a.X != b.X || a.Y != b.Y || a.Z != b.Z;
}

CoordStruct BuildingClass::unknown_slot44(int arg1)
{
    if (Coord_Differs(Type->ExitCoord, unknown_geometry_l)) {
        CoordStruct coord = Coord;
        return coord + Type->ExitCoord;
    }
    return Center_Coord();
}
