// void SliderClass::Set_Thumb_Size(int value) (0x00684980, slot 42)
// Thumb becomes value, at most MaxValue and at least 1.
#include "shared/gadget.hpp"

void SliderClass::Set_Thumb_Size(int value)
{
    Thumb = (value < MaxValue) ? value : MaxValue;
    Thumb = (Thumb > 1) ? Thumb : 1;
    Flag_To_Redraw();
    Recalc_Thumb();
}
