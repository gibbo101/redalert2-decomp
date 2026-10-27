// bool TechnoClass::unknown_slot39() (0x006CD290, slot 39)
// Owner test, then slots 201/202, the type flag +0xB04 and slot 114.
#include "shared/techno.hpp"
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0

bool TechnoClass::unknown_slot39()
{
    if (!House->Unknown_004F52B0()) {
        return false;
    }
    if (unknown_slot201()) {
        return false;
    }
    if (unknown_slot32()->Spawned) {
        return false;
    }
    if (unknown_slot202()) {
        return false;
    }
    return unknown_slot114() ? true : false;
}
