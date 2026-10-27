// WeaponTypeClass::WeaponTypeClass(NoInitClass const &noinit) (0x007330D0)
#include "shared/weapon_type.hpp"

WeaponTypeClass::WeaponTypeClass(NoInitClass const &noinit) :
    AbstractTypeClass(noinit),
    unknown_bc(noinit),
    Anim(noinit),
    unknown_fc(noinit),
    unknown_ff(noinit),
    unknown_102(noinit)
{
}
