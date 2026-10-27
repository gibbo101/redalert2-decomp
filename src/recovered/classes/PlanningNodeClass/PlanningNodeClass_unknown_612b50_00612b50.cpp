#define RA2_COORD_EQUAL_MEMBER
// void PlanningNodeClass::unknown_612b50(bool all) (0x00612B50)
// Forgets the node's computed index (and, with all, those of its branches).
#include "shared/planning.hpp"

void PlanningNodeClass::unknown_612b50(bool all)
{
    unknown_b4 = -1;
    if (all) {
        int count = Branches.Count();
        for (int i = 0; i < count; i++) {
            Branches[i]->unknown_74 = -1;
        }
        Branch.unknown_74 = -1;
    }
}
