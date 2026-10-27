// int GadgetClass::Clicked_On(unsigned &key, unsigned flags, int x, int y) (0x004CF0E0, slot 32)
// Runs Action when the gadget is stuck, has keyboard input, or the mouse
// event happened inside it.
#include "shared/gadget.hpp"

int GadgetClass::Clicked_On(unsigned &key, unsigned flags, int x, int y)
{
    flags &= Flags;
    if (this == StuckOn || (flags & KEYBOARD) ||
        (flags && (unsigned)(x - X) < (unsigned)Width && (unsigned)(y - Y) < (unsigned)Height)) {
        return Action(flags, key);
    }
    return false;
}
