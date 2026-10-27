// void ObjectClass::Detach(AbstractClass *target, bool all) (0x005D3BD0)
#include "shared/object_type.hpp"

void ObjectClass::Detach(AbstractClass *target, bool all)
{
    if (unknown_34 == target && unknown_34 != 0) {
        unknown_34->unknown_2c--;
        unknown_34 = 0;
    }
    if (all && target == unknown_30 && target != 0) {
        unknown_30 = unknown_30->unknown_30;
    }
}
