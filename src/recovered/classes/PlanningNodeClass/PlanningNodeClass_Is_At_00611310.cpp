#define RA2_COORD_EQUAL_MEMBER
// int PlanningNodeClass::Is_At(CoordStruct coord) const (0x00611310)
#include "shared/planning.hpp"

int PlanningNodeClass::Is_At(CoordStruct coord) const
{
    CoordStruct here = Coord();
    if (here.X == coord.X && here.Y == coord.Y && here.Z == coord.Z) {
        return 1;
    }
    return 0;
}
