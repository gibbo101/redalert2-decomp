// int BuildingLightClass::unknown_func_434610() const (0x00434610)
// The light's distance from its owner as a step: 0 inside the rules' near
// range (+0x6B4), then tenths of the span up to the far range (+0x6B0).
#include "shared/building_light.hpp"
#include "shared/rules.hpp"

int BuildingLightClass::unknown_func_434610() const
{
    CoordStruct diff = Center_Coord() - Owner->Center_Coord();
    int distance = (int)unknown_sqrt_4ba410((double)diff.X * diff.X + (double)diff.Z * diff.Z + (double)diff.Y * diff.Y);
    int near_range = Rules->unknown_6b4;
    if (distance < near_range) {
        return 0;
    }
    return (distance - near_range) / ((Rules->unknown_6b0 - near_range) / 10);
}
