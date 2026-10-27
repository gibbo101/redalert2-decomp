// void InfantryClass::Detach(AbstractClass *target, bool all) (0x00501CB0, slot 10)
#include "shared/infantry.hpp"
// @ref ?Detach@FootClass@@UAEXPAVAbstractClass@@_N@Z=004c8460

void InfantryClass::Detach(AbstractClass *target, bool all)
{
    FootClass::Detach(target, all);
    if (Type == target) {
        Type = 0;
    }
}
