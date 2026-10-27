// void AnimTypeClass::Detach(AbstractClass *target, bool all) (0x00426530)
#include "shared/anim_type.hpp"

void AnimTypeClass::Detach(AbstractClass *target, bool all)
{
    if (Next == target) {
        Next = 0;
    }
}
