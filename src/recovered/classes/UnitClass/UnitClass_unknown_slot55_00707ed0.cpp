// void UnitClass::unknown_slot55(TechnoClass *killer) (0x00707ED0, slot 55)
// Springs the tag's events 7 (only with a killer), 48 and 29 for this unit,
// unless +0x290 is set and the tag declines (0x006B41F0); then the techno
// behaviour.
#include "shared/unit.hpp"
// @ref ?unknown_func_6b41f0@TagClass@@QBE_NXZ=006b41f0
// @ref ?Unknown_006B3DF0@TagClass@@QAE_NHPAVObjectClass@@VCell@@HH@Z=006b3df0
// @ref ?unknown_cell_ad0488@@3VCell@@B=00ad0488
// @ref ?unknown_slot55@TechnoClass@@UAEXPAV1@@Z=006ced90

// A cell passed with the unit's events (0x00AD0488; meaning unknown).
extern Cell const unknown_cell_ad0488;

void UnitClass::unknown_slot55(TechnoClass *killer)
{
    if (unknown_34 && (unknown_290 == -1 || !unknown_34->unknown_func_6b41f0())) {
        if (killer != 0) {
            unknown_34->Unknown_006B3DF0(7, this, unknown_cell_ad0488, 0, 0);
        }
        if (unknown_34) {
            unknown_34->Unknown_006B3DF0(48, this, unknown_cell_ad0488, 0, 0);
        }
        if (unknown_34) {
            unknown_34->Unknown_006B3DF0(29, this, unknown_cell_ad0488, 0, 0);
        }
    }
    TechnoClass::unknown_slot55(killer);
}
