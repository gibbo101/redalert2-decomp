// void CellClass::unknown_47a340(AbstractClass *target) (0x0047A340): forgets
// target: the cell tag (and the tagged-cell entry), +0x2C, +0x30 and, for a
// fogged object (kind 0x3D), its entry in the fogged-object list.
#include "shared/cell.hpp"
#include "shared/tag.hpp"
// @ref ?unknown_map_tagged_cells_833638@@3V?$DynamicVectorClass@VCell@@@@A=00833638

void CellClass::unknown_47a340(AbstractClass *target)
{
    if (unknown_3c == target) {
        if (unknown_3c != 0) {
            unknown_3c->unknown_2c--;
        }
        unknown_3c = 0;
        unknown_map_tagged_cells_833638.Delete(MapCoords);
    }
    if (unknown_2c == target) {
        unknown_2c = 0;
    }
    if (unknown_30 == target) {
        unknown_30 = 0;
    }
    if (FoggedObjects != 0 && target->Kind_Of() == 0x3D) {
        FoggedObjects->Delete((FoggedObjectClass *)target);
    }
}
