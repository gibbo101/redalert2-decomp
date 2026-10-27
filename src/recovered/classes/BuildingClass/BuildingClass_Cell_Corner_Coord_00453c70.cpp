// Return the stored building coordinate offset by half a cell in X and Y.
// Slot42 uses the existing CoordStruct value result and hidden output pointer.
#include "shared/building.hpp"
CoordStruct BuildingClass::unknown_slot42() const
{
    CoordStruct position=Coord;
    return position-CoordStruct(128,128,0);
}
