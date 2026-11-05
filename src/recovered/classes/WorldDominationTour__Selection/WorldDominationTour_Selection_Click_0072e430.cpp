// void Selection::Click(Point2D const &point, bool &selected) (0x0072E430)
// Hover_At is a hypothesis: Hover's second Get_Territory stays out of line here, which needs one more
// inline level (or one pending site) over Hover.
// @ref ??_C@_0BB@COPA@ConflictSelected?$AA@=007fc470
#ifndef VECTOR_IMPLEMENT_ALL
#define VECTOR_IMPLEMENT_ALL
#endif
#include "shared/wdt_selection.hpp"
namespace WorldDominationTour {
// Never inlined: Choose_Territory 0x0072E050 calls it.
#pragma auto_inline(off)
void Selection::Click(Point2D const &point, bool &selected)
{
    switch (Region(point)) {
    case 2:
        TheMap->Set_Unknown_74(this, true);
        Cancel();
        break;
    case 1:
        TheMap->Set_Unknown_74(this, false);
        selected = Hover_At(point);
        if (selected) {
            Play_Sound("ConflictSelected");
        }
        break;
    }
}
#pragma auto_inline(on)
}
