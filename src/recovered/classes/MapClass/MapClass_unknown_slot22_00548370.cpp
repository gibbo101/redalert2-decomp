// void MapClass::unknown_slot22() (0x00548370, slot 22)
// Rebuilds the cell vector in place with MapCellTotal empty slots.
#include "shared/map.hpp"

void MapClass::unknown_slot22()
{
    new (&Cells) VectorClass<CellClass *>;
    Cells.Resize(MapCellTotal);
    for (int index = 0; index < MapCellTotal; index++) {
        Cells[index] = 0;
    }
}
