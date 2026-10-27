// int SliderClass::Bump(int up) (0x00684BB0, slot 43)
// Moves the value by a whole thumb.
#include "shared/gadget.hpp"

int SliderClass::Bump(int up)
{
    if (up) {
        return Set_Value(CurValue - Thumb);
    } else {
        return Set_Value(Thumb + CurValue);
    }
}
