// BaseNodeClass *BaseClass::Get_Node(BuildingClass const *building) (0x0042C2B0)
// The node a building of this house was placed for: same type and cell.
#include "shared/base.hpp"
#include "shared/techno.hpp"
#include "shared/building_type_class.hpp"

BaseNodeClass *BaseClass::Get_Node(BuildingClass *building)
{
    if (building->House == House) {
        for (int index = 0; index < Nodes.Count(); index++) {
            if (building->Type->ArrayIndex == Nodes[index].Type && building->unknown_slot104() == Nodes[index].Cell) {
                return &Nodes[index];
            }
        }
    }
    return 0;
}
