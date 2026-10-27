// WeaponTypeClass::~WeaponTypeClass() (0x00733120)
// Detaches the weapon type everywhere, forgets its projectile and warhead and
// leaves the weapon type list.
#include "shared/weapon_type.hpp"
// @ref ??1AbstractTypeClass@@UAE@XZ=00410740
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90

WeaponTypeClass::~WeaponTypeClass()
{
    Unknown_006ECB90(this, true);
    Projectile = 0;
    Warhead = 0;
    unknown_WeaponTypeClass_list_00839b90.Delete(this);
}
