// bool TechnoTypeClass::unknown_slot41() const (0x006DACC0)
// True when the primary weapon exists and PreventAttackMove is clear.
#include "shared/techno_type.hpp"
#include "shared/house.hpp"

bool TechnoTypeClass::unknown_slot41() const
{
    if (Weapon[0].WeaponType && !PreventAttackMove) {
        return true;
    }
    return false;
}
