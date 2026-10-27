// ShapeButtonClass *__fastcall TabClass::Unknown_006A0600(int slot) (0x006A0600)
// The button mapped to slot, or null when the map entry is out of range.
#include "shared/tab.hpp"
// @ref ?SlotButton@TabClass@@2PAHA=00abe2c8
// @ref ?Buttons@TabClass@@2PAVShapeButtonClass@@A=00abd918

ShapeButtonClass *__fastcall TabClass::Unknown_006A0600(int slot)
{
    int button = SlotButton[slot];
    if (button >= 0 && button < 25) {
        return &Buttons[button];
    }
    return 0;
}
