// bool TechnoTypeClass::Has_Turret_Weapons() const (0x006DF680)
// TurretCount= is positive.
#include "shared/techno_type.hpp"
#include "shared/house.hpp"

bool TechnoTypeClass::Has_Turret_Weapons() const
{
    return TurretCount > 0;
}
