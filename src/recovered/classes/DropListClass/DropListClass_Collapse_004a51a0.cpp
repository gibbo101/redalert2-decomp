// void DropListClass::Collapse() (0x004A51A0)
#include "shared/gadget.hpp"

void DropListClass::Collapse()
{
    if (IsDropped) {
        List.Remove();
        IsDropped = false;
    }
}
