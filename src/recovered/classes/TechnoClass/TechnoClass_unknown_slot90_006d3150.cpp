// int TechnoClass::unknown_slot90() (0x006D3150, slot 90)
// The type's +0x59C plus slot 168, plus slot 90 of every passenger when the
// owner's difficulty has ContentScan= set or the owner's
// +0x194 reaches rules +0x10B8. Names are hypotheses.
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_468a10@UnknownCargo@@QBEPAVObjectClass@@XZ=00468a10

int TechnoClass::unknown_slot90()
{
    int passengers = 0;
    HouseClass *house = House;
    if (Rules->Diff[house->unknown_c8].ContentScan || house->unknown_194 >= Rules->unknown_10b8) {
        if (Cargo.Object != 0) {
            for (ObjectClass *object = Cargo.unknown_468a10(); object != 0; object = object->unknown_30) {
                passengers += object->unknown_slot90();
            }
        }
    }
    return unknown_slot32()->unknown_59c + unknown_slot168() + passengers;
}
