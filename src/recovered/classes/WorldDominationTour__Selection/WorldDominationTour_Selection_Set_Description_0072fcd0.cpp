// void Selection::Set_Description(WideString const &text, int unknown2) (0x0072FCD0)
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
void Selection::Set_Description(WideString const &text, int unknown2)
{
    if (Description != 0) {
        Remove_Anim(Description);
        unknown_surface_839954->Copy_From(TheMap->DescriptionRect, *unknown_surface_839958, TheMap->DescriptionRect, false, true);
        Add_Rect(TheMap->DescriptionRect);
        Description = 0;
    }
    if (text.Length() > 0) {
        WideString copy(text);
        Description = new MSBitPrintAnim(copy, TheMap->DescriptionRect, true);
        Description->Set_Unknown_30(true);
        Add_Anim(Description);
    }
}
}
