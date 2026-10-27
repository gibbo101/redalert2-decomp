// bool TechnoTypeClass::Is_Two_Shooter() const (0x006DAF20)
// True when the primary fires twice: same secondary or a burst above one.
#include "shared/techno_type.hpp"
#include "shared/house.hpp"

bool TechnoTypeClass::Is_Two_Shooter() const
{
    WeaponTypeClass *primary = Weapon[0].WeaponType;
    if (primary) {
        WeaponTypeClass *secondary = Weapon[1].WeaponType;
        if (primary == secondary || primary->Burst > 1 || (secondary && secondary->Burst > 1)) {
            return true;
        }
    }
    return false;
}
