// int ListClass::Action(unsigned flags, unsigned &key) (0x0053A1F0, slot 31)
// A release ends the click; the up/down keys step the selection; a click
// selects the line under the mouse.
#include "shared/gadget.hpp"
#include "shared/mouse.hpp"
// @ref ?Action@ControlClass@@UAEHIAAI@Z=004834b0
// @ref ?WWMouse@@3PAVMouse@@A=00839c68

int ListClass::Action(unsigned flags, unsigned &key)
{
    if (flags & LEFTRELEASE) {
        key = 0;
        flags &= ~LEFTRELEASE;
        ControlClass::Action(flags, key);
        return true;
    } else {
        if (flags & KEYBOARD) {
            if (key == 0x26) {
                Step_Selected_Index(-1);
                key = 0;
            } else if (key == 0x28) {
                Step_Selected_Index(1);
                key = 0;
            } else {
                flags &= ~KEYBOARD;
            }
        } else {
            SelectedIndex = CurrentTopIndex + (WWMouse->Get_Mouse_Y() - Y - 1) / LineHeight;
            SelectedIndex = (SelectedIndex < List.Count() - 1) ? SelectedIndex : List.Count() - 1;
            if (SelectedIndex == -1) {
                SelectedIndex = 0;
            }
        }
    }
    return ControlClass::Action(flags, key);
}
