// CoordStruct BuildingClass::Center_Coord() const (0x00444080, slot 18)
// The coordinate offset to the middle of the foundation: (width - 1) and
// (height - 1) half cells (128 leptons each) in X and Y.
#include "shared/building.hpp"
// @ref ?Foundation_Height@BuildingTypeClass@@QBEH_N@Z=00458940
// @ref ?Width@BuildingTypeClass@@QBEHXZ=00458930

CoordStruct BuildingClass::Center_Coord() const
{
    int y = Type->Foundation_Height(false) * 128 - 128;
    int x = Type->Width() * 128 - 128;
    CoordStruct coord = Coord;
    coord.X += x;
    coord.Y += y;
    return coord;
}
