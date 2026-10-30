// ProgressBarClass::Outline (0x0042BA10): the border rectangle, when the bar has one.
#include "shared/progress_bar.hpp"
#include "shared/gadget.hpp"
#include "shared/mouse.hpp"
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"

void ProgressBarClass::Outline() const
{
    if (Is_Outlined()) {
        unknown_surface_83995c->Draw_Rect(Rect(X, Y, Width, Height), unknown_drawer_8323c4->Convert(BorderColor));
    }
}
