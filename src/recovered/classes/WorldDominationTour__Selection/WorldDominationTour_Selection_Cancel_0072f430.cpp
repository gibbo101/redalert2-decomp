// void Selection::Cancel() (0x0072F430)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
void Selection::Cancel()
{
    if (!TheMap->unknown_64.unknown_4) {
        TheMap->Set_Unknown_68(this, true);
        Play_Sound("MouseCancel");
        Set_Tooltip(StringTable::Load_String("WOL:WDTTerritoryBack", 0, "D:\\Ra2\\WDTSel.cpp", 894));
    }
}
}
// @ref ??_7?$VectorCursor@PAVMSSfxEntry@@V?$DynamicVectorClass@PAVMSSfxEntry@@@@@@6B@=007af37c
// @ref ?Set_Unknown_68@Map@WorldDominationTour@@QAEXPAVMSEngine@@_N@Z=0072a720
// @ref ??_C@_0BF@LJGG@WOL?3WDTTerritoryBack?$AA@=007fc484
// @ref ??_C@_0M@JGFA@MouseCancel?$AA@=007fc49c
// @ref ??_C@_0BC@PBP@D?3?2Ra2?2WDTSel?4cpp?$AA@=007fc31c
// @ref ??_G?$VectorCursor@PAVMSSfxEntry@@V?$DynamicVectorClass@PAVMSSfxEntry@@@@@@UAEPAXI@Z=007303b0
// @ref ??B?$VectorCursor@PAVMSSfxEntry@@V?$DynamicVectorClass@PAVMSSfxEntry@@@@@@UBE_NXZ=00730360
// @ref ??E?$VectorCursor@PAVMSSfxEntry@@V?$DynamicVectorClass@PAVMSSfxEntry@@@@@@UAEAAV0@XZ=00730410
// @ref ??F?$VectorCursor@PAVMSSfxEntry@@V?$DynamicVectorClass@PAVMSSfxEntry@@@@@@UAEAAV0@XZ=00730420
