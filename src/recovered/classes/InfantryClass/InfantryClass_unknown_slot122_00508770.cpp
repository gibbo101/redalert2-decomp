// bool InfantryClass::unknown_slot122() (0x00508770, slot 122)
// False under missions 6 and 21, +0x57D or +0x7A; otherwise true when the
// locomotor is not moving now (or the mission is 5, 15, or 1 with no
// +0x228) and the current sequence is unset or interruptible.
#include "shared/infantry.hpp"
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref ?unknown_do_controls_7a3474@@3PAUDoStruct@@A=007a3474

bool InfantryClass::unknown_slot122()
{
    if (Mission == 6 || Mission == 21 || unknown_57d || unknown_7a) {
        return false;
    }
    if (!Locomotor.Checked()->Is_Moving_Now() || unknown_slot91() == 5 || unknown_slot91() == 15
        || (unknown_slot91() == 1 && unknown_228 == 0)) {
        if (Sequence == -1 || unknown_do_controls_7a3474[Sequence].Interrupt) {
            return true;
        }
    }
    return false;
}
