#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::unknown_6120c0() (0x006120C0)
#include "shared/planning.hpp"

void PlanningNodeClass::unknown_6120c0()
{
    int count = Members.Count();
    for (int i = 0; i < count; i++) {
        TechnoClass *techno = Members[i]->Owner;
        if (techno->unknown_77) {
            techno->unknown_slot81();
        }
    }
}
