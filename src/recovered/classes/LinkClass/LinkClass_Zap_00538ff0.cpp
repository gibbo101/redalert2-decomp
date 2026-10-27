// void LinkClass::Zap() (0x00538FF0)
// Forgets both neighbours without unlinking them.
#include "shared/gadget.hpp"

void LinkClass::Zap()
{
    Next = 0;
    Prev = 0;
}
