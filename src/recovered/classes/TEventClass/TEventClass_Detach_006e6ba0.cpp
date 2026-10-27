// void TEventClass::Detach(AbstractClass *target, bool all) (0x006E6BA0)
#include "shared/object.hpp"

void TEventClass::Detach(AbstractClass *target, bool all)
{
    if ((AbstractClass *)Next == target) {
        Next = Next->Next;
    }
    if ((AbstractClass *)unknown_30 == target) {
        unknown_30 = 0;
    }
}
