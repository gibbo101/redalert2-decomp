// int CheckBoxClass::Draw_Me(int forced) (0x0047D150; TibSun checkbox.cpp): when the
// control draws, hides the mouse, draws the sunken box, fills its face grey (palette
// index 13) and, when on, green (index 4), then shows the mouse again.
#include "shared/gadget.hpp"
#include "shared/rect.hpp"
#include "shared/convert.hpp"
#include "shared/mouse.hpp"
#include "shared/text_print.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Draw_Box@@YIXABVRect@@H_N@Z=004973d0

int CheckBoxClass::Draw_Me(int forced)
{
    if (ControlClass::Draw_Me(forced)) {
        WWMouse->Hide_Mouse();
        Draw_Box(Rect(X, Y, Width, Height), 0, false);
        unknown_surface_83995c->Fill_Rect(Rect(X + 1, Y + 1, Width - 1, Height - 1), unknown_drawer_8323c4->Convert(13));
        if (IsOn) {
            unknown_surface_83995c->Fill_Rect(Rect(X + 1, Y + 1, Width - 1, Height - 1), unknown_drawer_8323c4->Convert(4));
        }
        WWMouse->Show_Mouse();
        return true;
    }
    return false;
}
