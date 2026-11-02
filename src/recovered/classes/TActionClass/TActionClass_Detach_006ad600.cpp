// void TActionClass::Detach(AbstractClass *target, bool all) (0x006AD600)
#include "shared/object.hpp"

void TActionClass::Detach(AbstractClass *target, bool all)
{
    if ((AbstractClass *)Next == target) {
        Next = Next->Next;
    }
    if ((AbstractClass *)unknown_30 == target) {
        unknown_30 = 0;
    }
    if (unknown_50 == target) {
        unknown_50 = 0;
    }
    if (unknown_4c == target) {
        unknown_4c = 0;
    }
}


