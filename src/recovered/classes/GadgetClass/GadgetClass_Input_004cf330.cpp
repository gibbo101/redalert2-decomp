// int GadgetClass::Input() (0x004CF330, slot 10)
// Reads one key or mouse event, tracks the gadget under the mouse
// (Mouse_Enter/Mouse_Leave), turns the event into gadget flags and offers it
// to the stuck gadget, the focused gadget, or each gadget of the list in
// turn; returns the (possibly changed) key.
#include "shared/gadget.hpp"
#include "shared/keyboard.hpp"
#include "shared/mouse.hpp"
// @ref ?Check@WWKeyboardClass@@QAEGXZ=005322d0
// @ref ?Get@WWKeyboardClass@@QAEGXZ=00532320
// @ref ?Down@WWKeyboardClass@@QAE_NG@Z=00532890
// @ref ?WWKeyboard@@3PAVWWKeyboardClass@@A=00832468
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?Extract_At@GadgetClass@@QAEPAV1@HH@Z=004cf290

int GadgetClass::Input()
{
    int forced = false;
    if (LastList != this) {
        LastList = this;
        forced = true;
        StuckOn = 0;
        Focused = 0;
    }

    unsigned key = WWKeyboard->Check();
    if (key) {
        key = WWKeyboard->Get();
    }

    int mousex;
    int mousey;
    if ((key & 0xFF) == 1 || (key & 0xFF) == 2) {
        mousex = WWKeyboard->MouseQX;
        mousey = WWKeyboard->MouseQY;
    } else {
        mousex = WWMouse->Get_Mouse_X();
        mousey = WWMouse->Get_Mouse_Y();
    }

    GadgetClass *over = Extract_At(mousex, mousey);
    if (over != MouseOver) {
        if (MouseOver != 0) {
            MouseOver->Mouse_Leave();
        }
        MouseOver = over;
        if (over != 0) {
            over->Mouse_Enter();
        }
    }

    unsigned flags;
    if (key != 0) {
        if (key == 1) {
            flags = LEFTPRESS;
        } else if (key == 2) {
            flags = 0x10;
        } else if (key == 0x801) {
            flags = LEFTRELEASE;
        } else {
            flags = (key == 0x802) ? 0x40 : KEYBOARD;
        }
    } else {
        flags = WWKeyboard->Down(1) ? LEFTHELD : 0x08;
        if (WWKeyboard->Down(2)) {
            flags |= 0x20;
        } else {
            flags |= 0x80;
        }
    }

    if (StuckOn != 0) {
        StuckOn->Draw_Me(false);
        GadgetClass *oldstuck = StuckOn;
        StuckOn->Clicked_On(key, flags, mousex, mousey);
        if (StuckOn != 0) {
            StuckOn->Draw_Me(false);
        } else {
            oldstuck->Draw_Me(false);
        }
        return key;
    }

    if (Focused != 0 && (flags & KEYBOARD)) {
        Focused->Draw_Me(false);
        Focused->Clicked_On(key, flags, mousex, mousey);
        if (Focused != 0) {
            Focused->Draw_Me(false);
        }
        return key;
    }

    GadgetClass *gadget = this;
    while (gadget != 0) {
        gadget->Draw_Me(forced);
        if (!gadget->IsDisabled && gadget->Clicked_On(key, flags, mousex, mousey)) {
            gadget->Draw_Me(false);
            break;
        }
        gadget = (GadgetClass *)gadget->Get_Next();
    }
    return key;
}
