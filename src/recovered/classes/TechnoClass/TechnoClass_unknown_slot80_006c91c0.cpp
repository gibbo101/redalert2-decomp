// bool TechnoClass::unknown_slot80() (0x006C91C0, slot 80)
// The ObjectClass version when allowed; then the tag event 0x21, slot 196 and 0x006145E0.
#include "shared/techno.hpp"
// @ref ?unknown_slot80@ObjectClass@@UAE_NXZ=005d2e70
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Unknown_006B3DF0@TagClass@@QAE_NHPAVObjectClass@@VCell@@HH@Z=006b3df0
// @ref ?unknown_6145e0@TechnoClass@@QAEXXZ=006145e0
// @ref ?unknown_b263d8@@3HA=00b263d8
// @ref _unknown_geometry_k=00ac0148
// @ref ?unknown_sound_enabled_7d88d6@@3_NA=007d88d6

bool TechnoClass::unknown_slot80()
{
    if ((unknown_373 || House->Unknown_004F52B0() || !unknown_b263d8) && ObjectClass::unknown_slot80()) {
        if (unknown_34) {
            unknown_34->Unknown_006B3DF0(0x21, this, unknown_geometry_k, 0, 0);
        }
        if (House->Unknown_004F52B0() && unknown_sound_enabled_7d88d6) {
            unknown_slot196();
        }
        unknown_6145e0();
        return true;
    }
    return false;
}
