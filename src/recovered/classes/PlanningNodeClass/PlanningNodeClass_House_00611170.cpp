#define RA2_COORD_EQUAL_MEMBER
// HouseClass *PlanningNodeClass::House() const (0x00611170)
#include "shared/planning.hpp"

HouseClass *PlanningNodeClass::House() const
{
    return Members[0]->Owner->House;
}
