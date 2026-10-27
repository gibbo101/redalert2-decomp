// bool TechnoClass::unknown_slot157() (0x006D6780, slot 157)
// Whether a self-healing techno (the type's SelfHealing or rank ability 9)
// heals this frame: on every interval of the rules' +0x1348 minutes when
// it is damaged but alive.
#include "shared/techno.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_6d7910@TechnoClass@@QAE_NH@Z=006d7910
// @ref ?Frame@@3HA=00a40d2c
// @ref __real@8@4008e100000000000000=0079b608

bool TechnoClass::unknown_slot157()
{
    if (!unknown_slot32()->SelfHealing && !unknown_6d7910(9)) {
        return false;
    }
    if (Frame % (int)(Rules->unknown_1348 * 900.0) != 0) {
        return false;
    }
    int strength = Strength;
    if (strength == unknown_slot32()->MaxStrength) {
        return false;
    }
    return strength != 0 ? true : false;
}
