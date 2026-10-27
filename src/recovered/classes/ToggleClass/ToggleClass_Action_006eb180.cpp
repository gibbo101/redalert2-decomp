// int ToggleClass::Action(unsigned flags, unsigned &key) (0x006EB180, slot 31)
// Tracks whether the button is pressed while the mouse is over it; a
// release over it toggles it (type 1) or turns it on (type 2).
#include "shared/gadget.hpp"
#include "shared/mouse.hpp"
// @ref ?Action@ControlClass@@UAEHIAAI@Z=004834b0
// @ref ?WWMouse@@3PAVMouse@@A=00839c68

int ToggleClass::Action(unsigned flags, unsigned &key)
{
    bool overbutton = (unsigned)(WWMouse->Get_Mouse_X() - X) < (unsigned)Width &&
                      (unsigned)(WWMouse->Get_Mouse_Y() - Y) < (unsigned)Height;

    if (!flags) {
        if (overbutton) {
            if (!IsPressed) {
                IsPressed = true;
                Flag_To_Redraw();
            }
        } else {
            if (IsPressed) {
                IsPressed = false;
                Flag_To_Redraw();
            }
        }
    }

    Sticky_Process(flags);

    if (flags & (LEFTPRESS | 0x10)) {
        IsPressed = true;
        Flag_To_Redraw();
        ControlClass::Action(flags & ~(LEFTPRESS | 0x10), key);
        key = 0;
        return true;
    }

    if (flags & (LEFTRELEASE | 0x40)) {
        if (IsPressed) {
            if (overbutton) {
                if (ToggleType == 1) {
                    IsOn = !IsOn;
                } else if (ToggleType == 2 && !IsOn) {
                    IsOn = true;
                }
            }
            IsPressed = false;
            Flag_To_Redraw();
        } else {
            flags &= ~(LEFTRELEASE | 0x40);
        }
    }
    return ControlClass::Action(flags, key);
}
