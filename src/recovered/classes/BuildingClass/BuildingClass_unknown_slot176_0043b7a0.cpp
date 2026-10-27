// int BuildingClass::unknown_slot176() (0x0043B7A0, slot 176)
// The negated height of the slot 110 value; a voxel turret's animation
// (Anims[9]) adds its ZAdjust.
#include "shared/building.hpp"
#include "shared/anim.hpp"
// @ref ?Unknown_006A2970@@YIHH@Z=006a2970

int BuildingClass::unknown_slot176()
{
    int height = -Unknown_006A2970(unknown_slot110());
    if (Type->TurretAnimIsVoxel) {
        return Type->Anims[9].ZAdjust + height;
    }
    return height;
}
