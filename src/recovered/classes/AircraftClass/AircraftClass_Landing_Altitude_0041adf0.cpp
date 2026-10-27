// int __stdcall AircraftClass::Landing_Altitude() (0x0041ADF0, IFlyControl slot 3)
// 100 for a carryall in radio contact or carrying (+0xFC), else 0; but 0
// while a free carryall on mission 7 is in contact with a building whose
// type has flag +0x1349 or +0x1365.
#include "shared/aircraft.hpp"
// @ref ?In_Radio_Contact@RadioClass@@QBE_NXZ=00636f10
// @ref ?Contact_With_Whom@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e20

int __stdcall AircraftClass::Landing_Altitude()
{
    if (Type->Carryall && Cargo.Object == 0 && In_Radio_Contact()) {
        TechnoClass *contact = Contact_With_Whom(0);
        if (unknown_slot91() == 7 && contact != 0 && contact->Kind_Of() == 6) {
            BuildingTypeClass *type = ((BuildingClass *)contact)->Type;
            if (type->unknown_1349 || type->unknown_1365) {
                return 0;
            }
        }
    }
    if ((In_Radio_Contact() && Type->Carryall) || (Cargo.Object != 0 && Type->Carryall)) {
        return 100;
    }
    return 0;
}
