// void TechnoClass::unknown_slot252(bool quiet) (0x006CF250, slot 252)
// Starts uncloaking from cloaked (2) or cloaking (1): state 3 counting the
// stage down from the last at the type's CloakingSpeed, with the rules'
// cloak sound unless quiet.
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/rules.hpp"
// @ref ?Voc_Play_At@@YIPAUAudioEvent@@HABUCoordStruct@@PAUAudioEventHandle@@@Z=00713e60

void TechnoClass::unknown_slot252(bool quiet)
{
    if (unknown_1b8 == 2 || unknown_1b8 == 1) {
        unknown_1b8 = 3;
        unknown_1bc.Value = Rules->unknown_548 - 1;
        unknown_1bc.Set_Rate(unknown_slot32()->CloakingSpeed);
        unknown_1bc.unknown_14 = -1;
        if (!quiet) {
            Voc_Play_At(Rules->unknown_5c0, CoordStruct(Coord), 0);
        }
    }
}
