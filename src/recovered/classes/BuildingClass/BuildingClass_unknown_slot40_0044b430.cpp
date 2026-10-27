// CoordStruct BuildingClass::unknown_slot40() (0x0044B430, slot 40)
// The center coordinate offset by the type's coordinate at +0xC48.
#include "shared/building.hpp"
// @ref ?Center_Coord@BuildingClass@@UBE?AUCoordStruct@@XZ=00444080

CoordStruct BuildingClass::unknown_slot40()
{
    CoordStruct center = Center_Coord();
    return Type->TargetCoordOffset + center;
}
