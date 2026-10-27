// void UnknownRectState_004321b0::unknown_reset_004321b0() -- 0x004321B0
// Purpose: resets the object's state: clears +0x04/+0x08/+0x0C/+0x20,
// stores 0x7FFF/0x3555 in the words at +0x24/+0x26 and 0x40 at +0x28, sets
// the flags +0x40/+0x41 and the ints +0x18/+0x1C/+0x2C to 1 and empties the
// rectangle at +0x30. Owner not identified.
#include "shared/unknown_rect_state.hpp"

void UnknownRectState_004321b0::unknown_reset_004321b0()
{
    unknown_04 = 0;
    unknown_20 = 0;
    unknown_0C = 0;
    unknown_08 = 0;
    unknown_24 = 0x7fff;
    unknown_26 = 0x3555;
    unknown_28 = 0x40;
    unknown_40 = true;
    unknown_41 = true;
    unknown_18 = 1;
    unknown_1C = 1;
    SetRect(&unknown_30, 0, 0, 0, 0);
    unknown_2C = 1;
}
