// bool TechnoClass::unknown_6d7910(int ability) (0x006D7910)
// Whether the techno's rank grants the type's ability: veterans (0x007133A0)
// the veteran ability, elites (0x00713420) the veteran or elite one.
#include "shared/techno.hpp"
// @ref ?unknown_7133a0@UnknownTechnoPair@@QBE_NXZ=007133a0
// @ref ?unknown_713420@UnknownTechnoPair@@QBE_NXZ=00713420

bool TechnoClass::unknown_6d7910(int ability)
{
    if (unknown_118.unknown_7133a0() || unknown_118.unknown_713420()) {
        TechnoTypeClass *type = unknown_slot32();
        if (unknown_118.unknown_7133a0() && type->VeteranAbilities.Ability[ability]) {
            return true;
        }
        if (unknown_118.unknown_713420() && (type->VeteranAbilities.Ability[ability] || type->EliteAbilities.Ability[ability])) {
            return true;
        }
    }
    return false;
}
