#define RA2_COORD_EQUAL_MEMBER
// bool PlanningTokenClass::Reached(int slot) const (0x00613B40)
// Whether the node at slot is at or past the first node of the path.
#include "shared/planning.hpp"

bool PlanningTokenClass::Reached(int slot) const
{
    if (unknown_8c == -1) {
        return false;
    }
    return slot >= unknown_8c;
}
