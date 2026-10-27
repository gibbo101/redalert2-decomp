// int TechnoClass::unknown_slot168() (0x006D3E50, slot 168)
// For a building with a positive 0x004532F0 value, that value times the rules +0xBE8; otherwise the type +0x598.
#include "shared/techno.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_4532f0@BuildingClass@@QAEHXZ=004532f0

int TechnoClass::unknown_slot168()
{
    TechnoTypeClass *type = unknown_slot32();
    if (type) {
        if (Kind_Of() == 6 && ((BuildingClass *)this)->unknown_4532f0() > 0) {
            int value = Rules->unknown_be8;
            return value * ((BuildingClass *)this)->unknown_4532f0();
        }
        return type->ThreatPosed;
    }
    return 0;
}
