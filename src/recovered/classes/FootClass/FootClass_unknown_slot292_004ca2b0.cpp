// bool FootClass::unknown_slot292() (0x004CA2B0)
// With no target (+0x494) and no TechnoClass target (+0x228): slot 261 with
// no target, passing whether the unit may leave — unless it is in mission
// 7 next to a building contact whose type sets +0x1349.
#include "shared/foot.hpp"
#include "shared/building_type.hpp"
#include "shared/building_type.hpp"
#include "shared/aircraft.hpp"
// @ref ?Contact@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e10

bool FootClass::unknown_slot292()
{
    if (unknown_494 == 0 && unknown_228 == 0) {
        TechnoClass *contact = Contact(0);
        BuildingClass *building = 0;
        if (contact != 0 && contact->Kind_Of() == 6) {
            building = (BuildingClass *)contact;
        }
        bool stay = (Mission == 7 && building != 0 && building->Type->UnitRepair) ? true : false;
        return unknown_slot261(0, !stay);
    }
    return false;
}
