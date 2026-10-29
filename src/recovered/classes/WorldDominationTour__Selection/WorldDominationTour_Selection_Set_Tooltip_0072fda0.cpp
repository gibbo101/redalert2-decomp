// void Selection::Set_Tooltip(WideString const &text) (0x0072FDA0)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
void Selection::Set_Tooltip(WideString const &text)
{
    Rect rect = TheMap->TooltipRect;
    if (Tooltip != 0) {
        Remove_Anim(Tooltip);
        unknown_surface_839954->Copy_From(rect, *unknown_surface_839958, rect, false, true);
        Add_Rect(rect);
        Tooltip = 0;
    }
    if (text.Length() > 0) {
        WideString copy(text);
        Tooltip = new MSBitPrintAnim(copy, rect, false);
        Tooltip->Set_Unknown_30(true);
        Add_Anim(Tooltip);
    }
}
}
