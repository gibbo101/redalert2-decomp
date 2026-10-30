// ProgressBarClass::Redraw (0x0042BA80): border, filled part, then the rest.
#include "shared/progress_bar.hpp"
#include "shared/gadget.hpp"
#include "shared/mouse.hpp"
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"

void ProgressBarClass::Redraw() const
{
    WWMouse->Hide_Mouse();
    Outline();

    int x = X;
    int y = Y;
    int w = Width;
    int h = Height;
    if (Is_Outlined()) {
        x += 1;
        y += 1;
        w -= 2;
        h -= 2;
    }

    int size = Is_Horizontal() ? w : h;
    int fill = CurrentValue * size;

    if (fill > 0) {
        if (Is_Horizontal()) {
            unknown_surface_83995c->Fill_Rect(Rect(x, y, fill, h), unknown_drawer_8323c4->Convert(BarColor));
        } else {
            unknown_surface_83995c->Fill_Rect(Rect(x, y + fill, w, h), unknown_drawer_8323c4->Convert(BarColor));
        }
    }

    if (w - fill > 0) {
        if (Is_Horizontal()) {
            unknown_surface_83995c->Fill_Rect(Rect(x + fill, y, w, h), unknown_drawer_8323c4->Convert(BackColor));
        } else {
            unknown_surface_83995c->Fill_Rect(Rect(x, y, w, fill - 1), unknown_drawer_8323c4->Convert(BackColor));
        }
    }
    WWMouse->Show_Mouse();

    ProgressBarClass *me = (ProgressBarClass *)this;
    me->LastDisplayCurrent = CurrentValue;
    me->IsDrawn = true;
}
