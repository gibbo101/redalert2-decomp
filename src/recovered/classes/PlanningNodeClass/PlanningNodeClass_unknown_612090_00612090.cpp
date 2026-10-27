#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::unknown_612090() (0x00612090)
#include "shared/planning.hpp"

void PlanningNodeClass::unknown_612090()
{
    int count = Members.Count();
    for (int i = 0; i < count; i++) {
        TechnoClass *techno = Members[i]->Owner;
        if (!techno->unknown_77) {
            techno->unknown_slot80();
        }
    }
}
