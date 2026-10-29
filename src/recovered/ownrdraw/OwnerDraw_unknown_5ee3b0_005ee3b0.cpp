// @ref ?unknown_tooltip_a737f0@OwnerDraw@@3UUnknownTooltipState@1@A=00a737f0
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Restores the screen under the tooltip and releases its surface.
bool unknown_5ee3b0()
{
    if (!unknown_tooltip_a737f0.shown_114) {
        return false;
    }
    if (unknown_tooltip_a737f0.drawn_118 != 1 && unknown_tooltip_a737f0.surface_10) {
            Rect area = unknown_tooltip_a737f0.rect_00;
            unknown_surface_839950->Copy_From(area, *unknown_tooltip_a737f0.surface_10, Rect(0, 0, area.Width, area.Height),
                                              false, true);
            unknown_tooltip_a737f0.drawn_118 = 1;
    }
    if (unknown_tooltip_a737f0.surface_10) {
        delete unknown_tooltip_a737f0.surface_10;
    }
    unknown_tooltip_a737f0.surface_10 = 0;
    unknown_tooltip_a737f0.shown_114 = 0;
    unknown_tooltip_a737f0.drawn_118 = 0;
    return true;
}

}
