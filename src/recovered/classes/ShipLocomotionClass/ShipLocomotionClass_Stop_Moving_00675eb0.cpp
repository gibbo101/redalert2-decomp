// void __stdcall ShipLocomotionClass::Stop_Moving() (0x00675EB0, ILocomotion 18)
// With a head-to coordinate, a train's locomotive also stops the cars
// coupled behind it. The speed fraction drops to at most 0.3 and the
// destination is cleared.
#include "shared/ship_locomotion.hpp"
// @ref ?unknown_coord_ab91c8@@3UCoordStruct@@A=00ab91c8
// @ref __real@8@3ffd99999a0000000000=007a96b8
// @ref __com_issue_error@4=00795940

#define Min(a, b) ((a) < (b) ? (a) : (b))

void __stdcall ShipLocomotionClass::Stop_Moving()
{
    if (unknown_40 != unknown_coord_ab91c8 && LinkedTo->unknown_slot32()->IsTrain && !((UnitClass *)LinkedTo)->unknown_5b8) {
        for (UnitClass *car = (UnitClass *)((UnitClass *)LinkedTo)->unknown_5b0; car != 0; ) {
            car->Locomotor.Checked()->Stop_Moving();
            car = (UnitClass *)car->unknown_5b0;
            if (car == 0 || car == car->unknown_5b0) {
                break;
            }
        }
    }
    unknown_50 = Min(unknown_50, 0.3f);
    unknown_34 = unknown_coord_ab91c8;
}
