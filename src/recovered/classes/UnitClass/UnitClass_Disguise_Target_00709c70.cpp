// Current slot255 signature is TechnoClass*, but original Kind_Of cases also
// accept CellClass(11) and TerrainClass(36). Preserve the declared ABI;
// the observed branch identities justify the local casts, not a global rewrite.
#include "shared/unit.hpp"
#include "shared/cell.hpp"
#include "shared/overlay_type.hpp"
// @ref ?OverlayTypes@@3V?$DynamicVectorClass@PAVOverlayTypeClass@@@@A=00a35de8
// @ref ?unknown_slot255@TechnoClass@@UAEXPAV1@@Z=006d8680
void UnitClass::unknown_slot255(TechnoClass *target)
{
    if (!target) return;
    switch (target->Kind_Of()) {
    case 1:
        if (!target->unknown_slot48()) return;
        unknown_40c = target->unknown_slot50(true);
        unknown_410 = target->unknown_slot51(true);
        break;
    case 11:
        if (!unknown_slot208(target)) return;
        unknown_40c = OverlayTypes[((CellClass *)target)->OverlayIndex];
        unknown_410 = 0;
        break;
    case 36:
        unknown_40c = target->Class_Of();
        unknown_410 = 0;
        TechnoClass::unknown_slot255(target);
        return;
    default:
        return;
    }
    TechnoClass::unknown_slot255(target);
}
