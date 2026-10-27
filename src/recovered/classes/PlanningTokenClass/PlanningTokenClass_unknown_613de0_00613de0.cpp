#define RA2_COORD_EQUAL_MEMBER
// void PlanningTokenClass::unknown_613de0() (0x00613DE0)
// Steps the loop start back one, never below 0.
#include "shared/planning.hpp"

void PlanningTokenClass::unknown_613de0()
{
    LoopStart = LoopStart - 1;
    LoopStart = LoopStart > 0 ? LoopStart : 0;
}
