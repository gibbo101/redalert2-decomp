// void MapClass::Unknown_005688A0(DynamicVectorClass<Cell> &cells) (0x005688A0)
// Recalculates a list of cells (TibSun Recalc_Cells_In_List): every listed
// cell in the local view loses its first subzone (the short at +0x6C's
// 10-byte entry) and recalculates (CellClass 0x00472540 with -1); then each
// such cell still without a subzone gets its subzones rebuilt (0x00566340).
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"

void MapClass::Unknown_005688A0(DynamicVectorClass<Cell> &cells)
{
    int index;
    for (index = cells.Count() - 1; index >= 0; index--) {
        if (Unknown_0055A660(cells[index], true)) {
            *(short *)(unknown_6c + Unknown_0054FAB0(cells[index]) * 10) = 0;
            CellClass *cellptr = &Map[cells[index]];
            cellptr->Unknown_00472540(-1);
        }
    }
    for (index = cells.Count() - 1; index >= 0; index--) {
        Cell cell = cells[index];
        if (Unknown_0055A660(cell, true)) {
            if (*(short *)(unknown_6c + Unknown_0054FAB0(cell) * 10) == 0) {
                Unknown_00566340(cell);
            }
        }
    }
}
