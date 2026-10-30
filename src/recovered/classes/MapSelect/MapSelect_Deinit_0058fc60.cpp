#include "shared/map_select.hpp"
// @ref ?Clear@MapSelectData@@QAEXXZ=005b0730
// Original keeps cleanup out of line in this unit: calls 0058fa0c, 0058fb5b.
#pragma auto_inline(off)
void MapSelect::Deinit_0058fc60()
{
    if(Font) { delete Font; Font=0; }
    if(OverlayDrawer) { delete OverlayDrawer; OverlayDrawer=0; }
    if(AnimDrawer) { delete AnimDrawer; AnimDrawer=0; }
    Choices.Clear();
}

#pragma auto_inline(on)
