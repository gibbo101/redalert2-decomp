// void TagTypeClass::Detach(AbstractClass *target, bool all) (0x006B4860)
#include "shared/object.hpp"

void TagTypeClass::Detach(AbstractClass *target, bool all)
{
    if ((AbstractClass *)Triggers == target) {
        Triggers = Triggers->Next;
    }
}
