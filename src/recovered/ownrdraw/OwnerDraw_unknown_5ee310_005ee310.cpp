// @ref ?unknown_tooltip_a737f0@OwnerDraw@@3UUnknownTooltipState@1@A=00a737f0
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Blits the tooltip's saved surface to the screen once.
bool unknown_5ee310()
{
    if (!unknown_tooltip_a737f0.shown_114) {
        return false;
    }
    if (unknown_tooltip_a737f0.drawn_118 == 1) {
        return false;
    }
    if (!unknown_tooltip_a737f0.surface_10) {
        return false;
    }
    Rect area = unknown_tooltip_a737f0.rect_00;
    unknown_surface_839950->Copy_From(area, *unknown_tooltip_a737f0.surface_10, Rect(0, 0, area.Width, area.Height),
                                      false, true);
    unknown_tooltip_a737f0.drawn_118 = 1;
    return true;
}

}
