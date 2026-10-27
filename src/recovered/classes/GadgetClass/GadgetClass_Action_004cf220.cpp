// int GadgetClass::Action(unsigned flags, unsigned &key) (0x004CF220, slot 31)
// Any event marks the gadget for redraw and updates the sticky state.
#include "shared/gadget.hpp"

int GadgetClass::Action(unsigned flags, unsigned &key)
{
    if (flags) {
        IsToRepaint = true;
        Sticky_Process(flags);
        return true;
    }
    return false;
}
