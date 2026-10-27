// void TechnoClass::unknown_slot253(bool quiet) (0x006CF300, slot 253)
// Starts cloaking from visible (0) or uncloaking (3): slot 54 first, then
// state 1 counting the stage up from 0 at the type's CloakingSpeed, with
// the rules' cloak sound unless quiet.
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/rules.hpp"
// @ref ?Unknown_00713E60@@YIXHABUCoordStruct@@H@Z=00713e60

void TechnoClass::unknown_slot253(bool quiet)
{
    if (unknown_1b8 == 0 || unknown_1b8 == 3) {
        unknown_slot54(false);
        unknown_1b8 = 1;
        unknown_1bc.Value = 0;
        unknown_1bc.Set_Rate(unknown_slot32()->CloakingSpeed);
        unknown_1bc.unknown_14 = 1;
        if (!quiet) {
            Unknown_00713E60(Rules->unknown_5c0, CoordStruct(Coord), 0);
        }
    }
}
