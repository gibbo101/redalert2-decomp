// void Selection::Show_Campaign() (0x0072FF30)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
void Selection::Show_Campaign()
{
    Set_Description(TheCampaign->Properties->LongDescription, 0);
    WideString tip(StringTable::Load_String("WDT:TerritorySelectToolTip", 0, "D:\\Ra2\\WDTSel.cpp", 1230));
    Set_Tooltip(tip);
}
}
// @ref ??_C@_0BL@MEDD@WDT?3TerritorySelectToolTip?$AA@=007fc454
// @ref ??_C@_0BC@PBP@D?3?2Ra2?2WDTSel?4cpp?$AA@=007fc31c
