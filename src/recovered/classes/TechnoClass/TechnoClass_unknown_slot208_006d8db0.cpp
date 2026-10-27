// bool TechnoClass::unknown_slot208(ObjectClass *target) (0x006D8DB0, slot 208)
// Whether the weapon slot 174 picks for target (flag +0x114) can engage it:
// kind 36 targets by the rules' +0x142D or that flag; with the flag, cells
// whose overlay type has +0x285, and active slot 48 objects without a slot
// 51 house.
#include "shared/techno.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_overlay_types_a35de8@@3V?$DynamicVectorClass@PAVUnknownOverlayType@@@@A=00a35de8

bool TechnoClass::unknown_slot208(ObjectClass *target)
{
    WeaponTypeClass *weapon = unknown_slot231(unknown_slot174((AbstractClass *)target))->WeaponType;
    if (weapon == 0) {
        return false;
    }
    if (target->Kind_Of() == 36) {
        if (Rules->unknown_142d || weapon->unknown_114) {
            return true;
        }
        return false;
    }
    if (!weapon->unknown_114) {
        return false;
    }
    if (target->Kind_Of() == 11 && ((UnknownTechnoCellView *)target)->Overlay != -1
        && unknown_overlay_types_a35de8[((UnknownTechnoCellView *)target)->Overlay]->unknown_285) {
        return true;
    }
    if (target != 0 && target->unknown_14_bit1 && target->unknown_slot48() && target->unknown_slot51(true) == 0) {
        return true;
    }
    return false;
}
