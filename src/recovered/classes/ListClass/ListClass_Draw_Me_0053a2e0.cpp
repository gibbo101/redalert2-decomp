// int ListClass::Draw_Me(int forced) (0x0053A2E0, slot 27)
// Draws the frame and the visible lines with the mouse hidden over them.
#include "shared/gadget.hpp"
#include "shared/mouse.hpp"
// @ref ?Draw_Me@GadgetClass@@UAEHH@Z=004cf240
// @ref ?Draw_Box@@YIXABVRect@@H_N@Z=004973d0

int ListClass::Draw_Me(int forced)
{
    if (GadgetClass::Draw_Me(forced)) {
        WWMouse->Conditional_Hide_Mouse(Rect(X, Y, Width, Height));
        Draw_Box(Rect(X, Y, Width, Height), 4, true);
        if (List.Count()) {
            for (int index = 0; index < LineCount; index++) {
                int line = CurrentTopIndex + index;
                if (List.Count() > line) {
                    Draw_Entry(line, X + 1, Y + LineHeight * index + 1, Width - 2, line == SelectedIndex);
                }
            }
        }
        WWMouse->Conditional_Show_Mouse();
        return true;
    }
    return false;
}
