// bool FlyLocomotionClass::unknown_4bcc60() (0x004BCC60)
// Landing check: a blocked cell flags the aircraft; a landed carrier (mission 4)
// unloads and frees its passengers, then both finishing slots are called.
// @ref ?Is_Civilian_Passenger_004139F0@@YI_NPAVFootClass@@@Z=004139f0
#include "shared/fly_locomotion.hpp"
#include "shared/cell.hpp"
#include "shared/aircraft.hpp"
#include "shared/map_view.hpp"
#include "shared/team.hpp"
#include "shared/house.hpp"

bool __fastcall Is_Civilian_Passenger_004139F0(FootClass *passenger);

bool FlyLocomotionClass::unknown_4bcc60()
{
    if (!Map.Unknown_0055A7F0(CoordStruct(LinkedTo->Coord))) {
        if (LinkedTo->unknown_slot91() == 4) {
            while (LinkedTo->Cargo.Object) {
                FootClass *passenger = (FootClass *)LinkedTo->Cargo.unknown_4689f0();
                if (Is_Civilian_Passenger_004139F0(passenger)) {
                    passenger->House->unknown_141 = true;
                }
                if (passenger->Team) {
                    passenger->Team->TargetNotAssigned = true;
                }
                delete passenger;
            }
            if (LinkedTo->Team) {
                LinkedTo->Team->TargetNotAssigned = true;
            }
            LinkedTo->unknown_slot210();
            LinkedTo->unknown_slot60();
            return true;
        }
    } else {
        LinkedTo->unknown_32d = true;
    }
    return false;
}
