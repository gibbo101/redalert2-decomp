// bool FootClass::unknown_slot37() (0x004C8940)
// True for kinds 1 and 2 in radio contact with a building whose type sets
// +0x1349 when within 128 leptons of it; otherwise ObjectClass's slot 37.
#include "shared/foot.hpp"
#include "shared/building_type.hpp"
#include "shared/building_type.hpp"
#include "shared/aircraft.hpp"
// @ref ?In_Radio_Contact@RadioClass@@QBE_NXZ=00636f10
// @ref ?Contact_With_Whom@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e20
// @ref ?unknown_slot37@ObjectClass@@UAE_NXZ=005d2c20

bool FootClass::unknown_slot37()
{
    int kind = Kind_Of();
    if (kind > 0 && kind <= 2 && In_Radio_Contact()) {
        if (Contact_With_Whom(0)->Kind_Of() == 6 && ((BuildingClass *)Contact_With_Whom(0))->Type->UnitRepair) {
            if (Coord_Length(Center_Coord() - Contact_With_Whom(0)->Center_Coord()) < 0x80) {
                return true;
            }
        }
    }
    return ObjectClass::unknown_slot37();
}
