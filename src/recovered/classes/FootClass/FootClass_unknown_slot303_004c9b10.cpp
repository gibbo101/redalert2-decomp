// int FootClass::unknown_slot303() (0x004C9B10)
// The unit's current speed (hypothesis: Westwood's Apparent_Speed): the
// type's speed (slot 206) times the house's factor for the type
// (0x004F5A20) and +0x470, times the rules' +0x598 with ability 0, times
// +0x468; a unit (kind 1) with +0x5B4 set moves at half that.
#include "shared/foot.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Unknown_004F5A20@HouseClass@@QAENPAVTechnoTypeClass@@@Z=004f5a20
// @ref ?unknown_6d7910@TechnoClass@@QAE_NH@Z=006d7910

int FootClass::unknown_slot303()
{
    int speed = (int)(unknown_slot206() * House->Unknown_004F5A20(unknown_slot32()) * unknown_470);
    if (unknown_6d7910(0)) {
        speed = (int)(speed * Rules->unknown_598);
    }
    int result = (int)(speed * unknown_468);
    if (Kind_Of() == 1 && ((UnitClass *)this)->unknown_5b4 != -1) {
        result /= 2;
    }
    return result;
}
