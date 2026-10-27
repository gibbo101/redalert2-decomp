#define RA2_COORD_EQUAL_MEMBER
// bool PlanningNodeClass::Is_Queued() const (0x00611720)
#include "shared/planning.hpp"

bool PlanningNodeClass::Is_Queued() const
{
    return IsQueued;
}
