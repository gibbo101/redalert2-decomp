#define RA2_COORD_EQUAL_MEMBER
// bool __fastcall Planning_Mission_Allows(TechnoClass *techno) (0x00615A10)
// Whether the techno's current mission lets planning mode take over: mission
// 5, or mission 1 / 0xB whose target is a building (kind 0xB) or, for 0xB,
// absent.
#include "shared/planning.hpp"

bool __fastcall Planning_Mission_Allows(TechnoClass *techno)
{
    if (techno) {
        int mission = techno->unknown_slot91();
        if (mission == 5) {
            return true;
        }
        TargetClass target = TargetClass(techno->unknown_228);
        if ((mission == 1 || mission == 0x0B) && (target.Kind == 0x0B || (mission == 0x0B && target.Kind == 0))) {
            return true;
        }
    }
    return false;
}
