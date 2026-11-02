// bool BuildingClass::unknown_44d900(BuildingTypeClass const *upgrade, HouseClass *house) (0x0044D900)
// Whether the upgrade type (named in its PowersUpBuilding at +0xC20) may
// power up this building for the house: the house must own it, the name
// must be the building's, and PowersUpToLevel allows another upgrade
// (-1: fewer than the type's Upgrades; 1 to 3: none yet).
#include "shared/building.hpp"
#include "shared/house.hpp"
// @ref __stricmp=00781f20

bool BuildingClass::unknown_44d900(BuildingTypeClass const *upgrade, HouseClass *house)
{
    if (house == House && _stricmp(upgrade->PowersUpBuilding, Type->ID) == 0) {
        int level = upgrade->PowersUpToLevel;
        if (level != -1) {
            if (level <= 0 || level > 3) {
                return false;
            }
        } else if (unknown_5c6 < Type->Upgrades) {
            return true;
        }
        if (unknown_5c6 == 0) {
            return true;
        }
    }
    return false;
}
