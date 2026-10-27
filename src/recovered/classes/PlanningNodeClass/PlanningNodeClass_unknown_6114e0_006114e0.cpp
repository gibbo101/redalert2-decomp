#define RA2_COORD_EQUAL_MEMBER
// int PlanningNodeClass::unknown_6114e0() const (0x006114E0)
#include "shared/planning.hpp"

int PlanningNodeClass::unknown_6114e0() const
{
    if (Branch.Count > 0 && unknown_b0 == -1) {
        return 1;
    }
    return 0;
}
