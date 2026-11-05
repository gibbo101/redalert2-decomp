#define RA2_COORD_EQUAL_MEMBER
// int PlanningNodeClass::Is_At(CoordStruct coord) const (0x00611310)
#include "shared/planning.hpp"

bool PlanningNodeClass::Is_At(CoordStruct coord) const
{
    CoordStruct here;
    here = Coord();
    CoordStruct const &node_coord = here;
    CoordStruct const &wanted = coord;
    CoordStruct const &left = node_coord;
    CoordStruct const &right = wanted;
    return left == right;
}
