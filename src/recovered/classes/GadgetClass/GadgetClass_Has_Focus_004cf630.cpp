// bool GadgetClass::Has_Focus() (0x004CF630, slot 22)
#include "shared/gadget.hpp"

bool GadgetClass::Has_Focus()
{
    return this == Focused;
}
