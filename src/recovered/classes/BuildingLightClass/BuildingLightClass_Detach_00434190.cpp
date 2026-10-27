// void BuildingLightClass::Detach(AbstractClass *target, bool all) (0x00434190)
// Forgets target as the followed object or the owner.
#include "shared/building_light.hpp"
// @ref ?Detach@ObjectClass@@UAEXPAVAbstractClass@@_N@Z=005d3bd0

void BuildingLightClass::Detach(AbstractClass *target, bool all)
{
    ObjectClass::Detach(target, all);
    if (Following == target) {
        Following = 0;
    }
    if (Owner == target) {
        Owner = 0;
    }
}
