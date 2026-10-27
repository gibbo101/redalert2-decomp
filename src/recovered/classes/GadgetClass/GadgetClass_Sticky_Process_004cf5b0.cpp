// void GadgetClass::Sticky_Process(unsigned flags) (0x004CF5B0, slot 30)
// A sticky gadget holds the mouse from a press until the release.
#include "shared/gadget.hpp"

void GadgetClass::Sticky_Process(unsigned flags)
{
    if (IsSticky && (flags & (LEFTPRESS | 0x10))) {
        StuckOn = this;
    }
    if (StuckOn == this && (flags & (LEFTRELEASE | 0x40))) {
        StuckOn = 0;
    }
}
