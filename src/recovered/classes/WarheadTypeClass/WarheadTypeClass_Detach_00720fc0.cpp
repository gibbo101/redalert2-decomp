// void WarheadTypeClass::Detach(AbstractClass *target, bool all) (0x00720FC0)
#include "shared/warhead_type.hpp"

void WarheadTypeClass::Detach(AbstractClass *target, bool all)
{
    if (target == (AbstractClass *)Particle) {
        Particle = 0;
    }
    AnimTypeClass *anim = (AnimTypeClass *)target;
    AnimList.Delete(anim);
}
