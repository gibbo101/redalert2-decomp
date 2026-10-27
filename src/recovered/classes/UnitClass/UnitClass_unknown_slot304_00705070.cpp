// void UnitClass::unknown_slot304() (0x00705070, slot 304)
// A computer-owned crusher (or one with ability 17) next to a crushable
// target, with no destination, or a BalloonHover unit, goes for the target
// at +0x228 (slot 260); otherwise the foot behaviour.
#include "shared/unit.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0
// @ref ?unknown_6d7910@TechnoClass@@QAE_NH@Z=006d7910
// @ref ?unknown_5d4c00@ObjectClass@@QAEHPAVAbstractClass@@@Z=005d4c00
// @ref ?unknown_slot304@FootClass@@UAEXXZ=004c4c30

// The target as an object (an inline cast helper; hypothesis).
static inline ObjectClass *As_Object(AbstractClass *target)
{
    return !target ? 0 : (target->unknown_14_bit0 ? (ObjectClass *)target : 0);
}

void UnitClass::unknown_slot304()
{
    if (!House->Unknown_004F52F0() && unknown_228 && !unknown_494) {
        ObjectClass *object = As_Object(unknown_228);
        if ((Type->Crusher || unknown_6d7910(17)) && unknown_5d4c00(unknown_228) < Rules->unknown_1390
            && object && object->Class_Of()->unknown_1fd && (Type->AutoCrush || !House->Unknown_004F52F0())) {
            unknown_slot260(unknown_228, 1);
            return;
        }
    }
    if (Type->BalloonHover) {
        unknown_slot260(unknown_228, 1);
        return;
    }
    FootClass::unknown_slot304();
}
