// bool InfantryClass::unknown_slot257() (0x00508320, slot 257)
// TechnoClass's answer, but false while moving, prone (+0x5C3), +0x57D or
// deploying (27-30), and only for sequences 0, 1 and 16.
#include "shared/infantry.hpp"
// @ref ?unknown_slot257@TechnoClass@@UAE_NXZ=006d4890
// @ref ?_com_issue_error@@YGXJ@Z=00795940

bool InfantryClass::unknown_slot257()
{
    if (!TechnoClass::unknown_slot257()) {
        return false;
    }
    if (Locomotor.Checked()->Is_Moving()) {
        return false;
    }
    if (unknown_5c3) {
        return false;
    }
    if (unknown_57d) {
        return false;
    }
    if (unknown_5090d0()) {
        return false;
    }
    if (Sequence == 1 || Sequence == 0 || Sequence == 16) {
        return true;
    }
    return false;
}
