// int SliderClass::Action(unsigned flags, unsigned &key) (0x00684B10, slot 31)
// A left press before the thumb bumps the value down a thumb, one after it bumps it up;
// a press on the thumb itself goes to the gauge. The key is consumed either way.
#include "shared/gadget.hpp"
#include "shared/mouse.hpp"

int SliderClass::Action(unsigned flags, unsigned &key)
{
    if (flags & LEFTPRESS) {
        int mouse;
        int edge;

        if (IsHorizontal) {
            mouse = WWMouse->Get_Mouse_X();
            edge = X;
        } else {
            mouse = WWMouse->Get_Mouse_Y();
            edge = Y;
        }
        edge += 1;

        if (mouse < edge + ThumbStart) {
            Bump(true);
            GaugeClass::Action(0, key);
            key = 0;
            return true;
        } else {
            if (mouse > edge + ThumbStart + ThumbSize) {
                Bump(false);
                GaugeClass::Action(0, key);
                key = 0;
                return true;
            } else {
                GaugeClass::Action(flags, key);
                key = 0;
                return true;
            }
        }
    }

    return GaugeClass::Action(flags, key);
}
