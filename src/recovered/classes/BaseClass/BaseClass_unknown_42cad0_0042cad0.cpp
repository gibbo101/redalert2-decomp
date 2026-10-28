// void BaseClass::unknown_42cad0(BuildingClass *building) (0x0042CAD0)
// Marks the node of a building (+0x08 set, +0x0C cleared).
#include "shared/base.hpp"

void BaseClass::unknown_42cad0(BuildingClass *building)
{
    BaseNodeClass *node = Get_Node(building);
    if (node != 0) {
        node->unknown_08 = true;
        node->unknown_0c = 0;
    }
}
