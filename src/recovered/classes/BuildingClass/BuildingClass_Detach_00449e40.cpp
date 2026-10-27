// void BuildingClass::Detach(AbstractClass *target, bool all) (0x00449E40, slot 10)
// The techno detach, then clears every member that refers to the target;
// restarts animation 17 (damaged variant below the yellow health ratio) when
// the target was the animation at +0x474; an animation target leaves the
// eight at +0x49C (or goes through 0x0044CCE0).
#include "shared/building.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Detach@TechnoClass@@UAEXPAVAbstractClass@@_N@Z=006d2d10
// @ref ?Health_Ratio@ObjectClass@@QBENXZ=005d4540
// @ref ?unknown_44cce0@BuildingClass@@QAEXPAVAbstractClass@@@Z=0044cce0

void BuildingClass::Detach(AbstractClass *target, bool all)
{
    TechnoClass::Detach(target, all);
    if (unknown_438 == target) {
        unknown_438 = 0;
    }
    if (unknown_440 == target) {
        unknown_440 = 0;
    }
    if (unknown_41c == target) {
        unknown_41c = 0;
    }
    if (unknown_4d4 == target) {
        unknown_4d4 = 0;
    }
    if (unknown_4e8 == target) {
        unknown_4e8 = 0;
    }
    if (unknown_454[8] == target) {
        unknown_44c920(17, Health_Ratio() <= Rules->unknown_1368, false, 0);
    }
    if (target && target->What_Am_I() == 4) {
        for (int index = 0; index < 8; index++) {
            if (unknown_49c[index] == target) {
                unknown_49c[index] = 0;
                return;
            }
        }
        if (((AnimClass *)target)->unknown_100) {
            unknown_44cce0(target);
            return;
        }
    }
    if (Type == target) {
        Type = 0;
    }
    for (int index = 0; index < 3; index++) {
        if (unknown_4c0[index] == target) {
            unknown_4c0[index] = 0;
        }
    }
    unknown_53c.Delete((InfantryClass *)target);
}
