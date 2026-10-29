// void Selection::Uncancel() (0x0072F540)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
void Selection::Uncancel()
{
    if (TheMap->unknown_64.unknown_4) {
        TheMap->Set_Unknown_68(this, false);
        Set_Tooltip(StringTable::Load_String("WDT:TerritorySelectToolTip", 0, "D:\\Ra2\\WDTSel.cpp", 916));
    }
}
}
// @ref ?Set_Unknown_68@Map@WorldDominationTour@@QAEXPAVMSEngine@@_N@Z=0072a720
// @ref ??_C@_0BL@MEDD@WDT?3TerritorySelectToolTip?$AA@=007fc454
// @ref ??_C@_0BC@PBP@D?3?2Ra2?2WDTSel?4cpp?$AA@=007fc31c
