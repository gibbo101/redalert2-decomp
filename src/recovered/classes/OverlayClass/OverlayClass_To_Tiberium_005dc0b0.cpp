// static int __fastcall OverlayClass::To_Tiberium(int overlay) (0x005DC0B0)
// The tiberium type whose overlay range (image, then image variants)
// contains the overlay; -1 for non-tiberium overlays, 0 with a debug
// message when no tiberium claims it.
#include "shared/overlay.hpp"
// @ref ??_C@_0CA@JBKJ@Overlay?5?$CFs?5not?5really?5tiberium?6?$AA@=007e8b60
#include "shared/tiberium.hpp"
#include "shared/debug_printf.hpp"
// @ref ?unknown_TiberiumClass_list_00ac0b30@@3V?$DynamicVectorClass@PAVTiberiumClass@@@@A=00ac0b30
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0


int __fastcall OverlayClass::To_Tiberium(int overlay)
{
    OverlayTypeClass *type;
    if (overlay != -1 && (type = OverlayTypes[overlay])->Tiberium) {
        for (int index = 0; index < unknown_TiberiumClass_list_00ac0b30.Count(); index++) {
            TiberiumClass *tiberium = unknown_TiberiumClass_list_00ac0b30[index];
            int first = tiberium->Image->ArrayIndex;
            if ((overlay >= first && overlay < first + tiberium->NumFrames) ||
                (overlay >= first + tiberium->NumFrames && overlay < first + tiberium->NumFrames + tiberium->NumImages)) {
                return tiberium->ArrayIndex;
            }
        }
        Debug_Printf("Overlay %s not really tiberium\n", type->Name);
        return 0;
    }
    return -1;
}
