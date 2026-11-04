// int InfantryClass::unknown_slot218(AbstractClass *target, int weapon, bool check_range) (0x00503A60, slot 218)
// Fire check: 6 during sequences 11-15, 20, 21 and 34-36; when 0x006C16F0
// (-1) is negative only infantry targets below the rules health ratio at
// +0x1360 are allowed (else 5). Then TechnoClass's answer; when that allows
// firing: 7 while +0x468 exceeds 0.1, or with +0x494 in an uninterruptible
// sequence or with a weapon flagged +0x105; 5 for weapons flagged +0x126 at
// anything but slot 105's object, and for IvanBomb warheads at objects
// already carrying a bomb; otherwise the locomotor's slot 35 when non-zero.
#include "shared/infantry.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_6c16f0@TechnoClass@@QAEHH@Z=006c16f0
// @ref ?Health_Ratio@ObjectClass@@QBENXZ=005d4540
// @ref ?unknown_slot218@TechnoClass@@UAEHPAVAbstractClass@@H_N@Z=006c9260
// @ref ?unknown_do_controls_7a3474@@3PAUDoStruct@@A=007a3474
// @ref ?_com_issue_error@@YGXJ@Z=00795940
// @ref __real@8@3ffbccccccccccccd000=0079c570

int InfantryClass::unknown_slot218(AbstractClass *target, int weapon, bool check_range)
{
    if (Is_Busy_Sequence(Sequence)) {
        return 6;
    }
    if (unknown_6c16f0(-1) < 0) {
        if (target == 0 || target->Kind_Of() != 15
            || !(((ObjectClass *)target)->Health_Ratio() < Rules->unknown_1360)) {
            return 5;
        }
    }
    int result = TechnoClass::unknown_slot218(target, weapon, check_range);
    if (result == 0) {
        if (unknown_468 > 0.1
            || (unknown_494 != 0 && Sequence != -1 && !unknown_do_controls_7a3474[Sequence].Interrupt)) {
            return 7;
        }
        WeaponTypeClass *weapon_type = unknown_slot231(weapon)->WeaponType;
        if (weapon_type != 0) {
            if (weapon_type->unknown_105 && unknown_494 != 0) {
                return 7;
            }
            if (weapon_type->unknown_126 && target != unknown_slot105()) {
                return 5;
            }
            WarheadTypeClass *warhead = weapon_type->Warhead;
            if (warhead != 0 && warhead->IvanBomb && target != 0 && ((ObjectClass *)target)->AbstractFlags.IsObject
                && ((ObjectClass *)target)->unknown_38 != 0) {
                return 5;
            }
        }
        int state = Locomotor.Checked()->State();
        if (state != 0) {
            return state;
        }
    }
    return result;
}
