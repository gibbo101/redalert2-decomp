// int __stdcall AircraftClass::Landing_Direction() (0x0041AEB0, IFlyControl slot 4)
// One of eight directions: the radio contact's facing (+0x2E0), else this
// aircraft's +0x2F8 facing when +0xFC is set, else the rules default.
#include "shared/aircraft.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?In_Radio_Contact@RadioClass@@QBE_NXZ=00636f10
// @ref ?Contact_With_Whom@RadioClass@@QBEPAVTechnoClass@@H@Z=00636e20
// @ref ?Current@FacingClass@@QBE?AUUnknownFacingDir@@XZ=004b8be0

int __stdcall AircraftClass::Landing_Direction()
{
    if (In_Radio_Contact()) {
        TechnoClass *contact = Contact_With_Whom(0);
        return Dir_To_8(contact->unknown_2e0.Current());
    }
    if (Cargo.Object != 0) {
        return Dir_To_8(unknown_2f8.Current());
    }
    return Rules->unknown_50;
}
