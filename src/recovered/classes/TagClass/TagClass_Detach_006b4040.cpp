// void TagClass::Detach(AbstractClass *target, bool all) (0x006B4040)
// A tag that loses its type queues itself for removal.
#include "shared/object.hpp"

void TagClass::Detach(AbstractClass *target, bool all)
{
    if ((AbstractClass *)Class == target) {
        Class = 0;
    }
    if ((AbstractClass *)AttachedTrigger == target) {
        AttachedTrigger = AttachedTrigger->Next;
    }
    if (Class == 0) {
        unknown_func_6b3cc0();
    }
}
