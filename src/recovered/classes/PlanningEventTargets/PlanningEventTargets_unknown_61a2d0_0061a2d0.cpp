#define RA2_COORD_EQUAL_MEMBER
// int PlanningEventTargets::unknown_61a2d0() const (0x0061A2D0)
#include "shared/planning.hpp"
// @ref ?Unknown_006F6750@PlanningEventTargets@@SAHXZ=006f6750
// @ref ?Unknown_006F6760@PlanningEventTargets@@SAHXZ=006f6760

int PlanningEventTargets::unknown_61a2d0() const
{
    int kind = (signed char)unknown_0c;
    if (kind == 0x0B) {
        return Unknown_006F6760();
    }
    if (kind == 0x1D) {
        return Unknown_006F6750();
    }
    return -1;
}
