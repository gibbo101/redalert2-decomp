// int GaugeClass::Action(unsigned flags, unsigned &key) (0x004D0420, slot 31)
// Dragging the thumb sets the value under the mouse (minus the grab offset
// within the thumb). An unchanged value consumes the input.
#include "shared/gadget.hpp"
#include "shared/mouse.hpp"
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?StuckOn@GadgetClass@@2PAV1@A=00865ff0
// @ref ?Action@ControlClass@@UAEHIAAI@Z=004834b0

int GaugeClass::Action(unsigned flags, unsigned &key)
{
    if (!HasThumb) {
        return false;
    }
    Sticky_Process(flags);
    if ((flags & LEFTPRESS) || ((flags & LEFTHELD) && StuckOn == this)) {
        if (flags & LEFTPRESS) {
            int curpix = Value_To_Pixel(CurValue);
            int clickpix = IsHorizontal ? WWMouse->Get_Mouse_X() : WWMouse->Get_Mouse_Y();
            if (clickpix > curpix && clickpix - curpix < Thumb_Pixels()) {
                ClickDiff = clickpix - curpix;
            } else {
                ClickDiff = 0;
            }
            int testval = Pixel_To_Value(IsHorizontal ? WWMouse->Get_Mouse_X() - ClickDiff : WWMouse->Get_Mouse_Y() - ClickDiff);
            while (testval < CurValue && ClickDiff > 0) {
                ClickDiff--;
                testval = Pixel_To_Value(IsHorizontal ? WWMouse->Get_Mouse_X() - ClickDiff : WWMouse->Get_Mouse_Y() - ClickDiff);
            }
        }
        if (!Set_Value(Pixel_To_Value(IsHorizontal ? WWMouse->Get_Mouse_X() - ClickDiff : WWMouse->Get_Mouse_Y() - ClickDiff))) {
            ControlClass::Action(0, key);
            key = 0;
            return true;
        }
    } else {
        flags &= ~LEFTHELD;
    }
    return ControlClass::Action(flags, key);
}
