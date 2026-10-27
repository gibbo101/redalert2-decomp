// void AircraftClass::Detach(AbstractClass *target, bool all) (0x0041ADB0, slot 10)
// FootClass::Detach, then forgets target as +0x5B4 or as the type.
#include "shared/aircraft.hpp"
// @ref ?Detach@FootClass@@UAEXPAVAbstractClass@@_N@Z=004c8460

void AircraftClass::Detach(AbstractClass *target, bool all)
{
    FootClass::Detach(target, all);
    if (unknown_5b4 == target) {
        unknown_5b4 = 0;
    }
    if (Type == target) {
        Type = 0;
    }
}
