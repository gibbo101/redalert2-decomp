// void CellClass::Set_unknown_3c(TagClass *tag) (0x0047A460): attaches the
// cell tag: the old tag's carrier count drops, a new one is counted and the
// cell joins the map's tagged-cell list.
#include "shared/cell.hpp"
#include "shared/tag.hpp"
// @ref ?unknown_map_tagged_cells_833638@@3V?$DynamicVectorClass@VCell@@@@A=00833638

void CellClass::Set_unknown_3c(TagClass *tag)
{
    if (unknown_3c != 0) {
        unknown_3c->unknown_2c--;
    }
    unknown_3c = tag;
    if (tag != 0) {
        unknown_map_tagged_cells_833638.Add(MapCoords);
        unknown_3c->unknown_2c++;
    }
}
