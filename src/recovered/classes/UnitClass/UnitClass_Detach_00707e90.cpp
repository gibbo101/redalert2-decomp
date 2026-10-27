// void UnitClass::Detach(AbstractClass *target, bool all) (0x00707E90, slot 10)
// FootClass::Detach, then forgets target as +0x5B0 or as the type.
#include "shared/unit.hpp"
// @ref ?Detach@FootClass@@UAEXPAVAbstractClass@@_N@Z=004c8460

void UnitClass::Detach(AbstractClass *target, bool all)
{
    FootClass::Detach(target, all);
    if (unknown_5b0 == target) {
        unknown_5b0 = 0;
    }
    if (Type == target) {
        Type = 0;
    }
}
