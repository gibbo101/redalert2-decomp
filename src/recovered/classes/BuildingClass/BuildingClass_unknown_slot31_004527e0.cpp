// bool BuildingClass::unknown_slot31() (0x004527E0, slot 31)
// True when the type undeploys into a unit and its flag at +0x1353 is clear.
#include "shared/building.hpp"

bool BuildingClass::unknown_slot31()
{
    if (!Type->UndeploysInto) {
        return false;
    }
    return Type->ConstructionYard ? false : true;
}
