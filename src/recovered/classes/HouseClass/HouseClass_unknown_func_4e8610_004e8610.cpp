// CoordStruct HouseClass::unknown_func_4e8610(int arg) const (0x004E8610)
// Returns the zero coordinate (this unit's copy of unknown_geometry_l, 0x00A40F48);
// the argument is unused. No caller in the image; owner and name are hypotheses.
#include "shared/house.hpp"
#include "shared/unknown_geometry.hpp"

CoordStruct HouseClass::unknown_func_4e8610(int arg) const
{
    return unknown_geometry_l;
}
