// int TemporalClass::Get_Warp_Per_Step(int step) (0x006E2470)
// The owner's current weapon damage (kept in +0x4C) plus that of every helper chained after it
// (followed at most 50 deep).
#include "shared/temporal.hpp"
#include "shared/techno.hpp"

int TemporalClass::Get_Warp_Per_Step(int step)
{
    int helpers = 0;
    if (unknown_44 != 0 && step <= 50) {
        helpers = unknown_44->Get_Warp_Per_Step(step + 1);
    }
    unknown_4c = Owner->unknown_slot231(Owner->unknown_slot174(0))->WeaponType->unknown_a4;
    return unknown_4c + helpers;
}
