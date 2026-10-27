// int SliderClass::Step(int up) (0x00684BF0, slot 44)
// Moves the value by one.
#include "shared/gadget.hpp"

int SliderClass::Step(int up)
{
    if (up) {
        return Set_Value(CurValue - 1);
    } else {
        return Set_Value(CurValue + 1);
    }
}
