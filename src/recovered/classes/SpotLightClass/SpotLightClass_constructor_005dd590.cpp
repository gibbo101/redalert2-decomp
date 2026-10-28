// SpotLightClass::SpotLightClass(CoordStruct coord, int size) (0x005DD590)
#include "shared/spot_light.hpp"

SpotLightClass::SpotLightClass(CoordStruct coord, int size) :
    Coord(coord),
    unknown_0c(0),
    unknown_10(size),
    unknown_14(0)
{
    unknown_SpotLightClass_list_00a731c0.Add(this);
}
