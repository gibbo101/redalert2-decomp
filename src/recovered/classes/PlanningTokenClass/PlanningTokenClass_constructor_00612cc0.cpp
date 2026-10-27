#define RA2_COORD_EQUAL_MEMBER
// PlanningTokenClass::PlanningTokenClass(TechnoClass *owner) (0x00612CC0)
#include "shared/planning.hpp"

PlanningTokenClass::PlanningTokenClass(TechnoClass *owner)
    : unknown_1c(false)
{
    unknown_8c = -1;
    LoopLength = -1;
    LoopStart = -1;
    unknown_98 = false;
    unknown_99 = false;
    Owner = owner;
}
