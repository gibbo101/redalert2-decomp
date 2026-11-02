// bool BaseClass::Is_Node(BuildingClass *building) (0x0042C210)
// Whether a building of this house stands on one of the base's nodes (TibSun Is_Node;
// Get_Node expands inline; the if/else form renumbers labels and moves a load in Read_INI 0x42C460).
#include "shared/base.hpp"

bool BaseClass::Is_Node(BuildingClass *building)
{
    if (Get_Node(building) != 0) {
        return true;
    }
    return false;
}
