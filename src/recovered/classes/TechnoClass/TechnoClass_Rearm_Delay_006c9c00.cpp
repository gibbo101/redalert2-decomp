// Rearm delay for a selected weapon; existing slot187 ABI is preserved.
#include "shared/techno.hpp"
#include "shared/foot.hpp"
#include "shared/weapon_type.hpp"
#include "shared/id_source.hpp"
#include "shared/rules.hpp"
int TechnoClass::unknown_slot187(int which)
{
    if (Kind_Of()==6 && unknown_254>1) return 1;
    WeaponTypeClass *weapon=unknown_slot231(which)->WeaponType;
    if (!weapon) return 1;
    if (weapon->unknown_10c || (weapon->unknown_106 && unknown_25c[1]) ||
        (weapon->unknown_105 && unknown_25c[0]) || (weapon->unknown_109 && unknown_25c[4])) {
        return weapon->unknown_b0;
    }
    UnitClass *unit;
    if (!this) unit=0;
    else unit=Kind_Of()==1 ? static_cast<UnitClass *>(this) : 0;
    if (unknown_310<weapon->Burst) {
        int delay=-1;
        if (unknown_310>0 && unknown_310<=4 && unit) delay=unit->Type->BurstDelay[unknown_310-1];
        return delay!=-1 ? delay : Random_Pick(3,5);
    } else {
        int delay=weapon->unknown_b0*House->unknown_f0+Random_Pick(0,2);
        if (unknown_118.unknown_7133a0() || unknown_118.unknown_713420()) {
            TechnoTypeClass *type=unknown_slot32();
            if ((unknown_118.unknown_7133a0() && type->VeteranAbilities.Ability[4]) ||
                (unknown_118.unknown_713420() && (type->VeteranAbilities.Ability[4] || type->EliteAbilities.Ability[4]))) {
                delay=delay*Rules->VeteranROF;
            }
        }
        if (Kind_Of()==6 && static_cast<BuildingClass *>(this)->unknown_4532f0()>0) {
            delay/=static_cast<BuildingClass *>(this)->unknown_4532f0();
        }
        return delay;
    }
}
