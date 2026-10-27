#define RA2_COORD_EQUAL_MEMBER
// int PlanningTokenClass::unknown_613d80() const (0x00613D80)
// False while the loop start is negative (no loop).
#include "shared/planning.hpp"

int PlanningTokenClass::unknown_613d80() const
{
    if (LoopStart <= 0 && LoopStart != 0) {
        return 0;
    }
    return 1;
}
