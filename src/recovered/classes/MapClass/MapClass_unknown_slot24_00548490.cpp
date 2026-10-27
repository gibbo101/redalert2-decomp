// void MapClass::unknown_slot24() (0x00548490, slot 24)
// Re-constructs every existing cell in place, row by row.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
// @ref ??0CellClass@@QAE@XZ=00470f10

void MapClass::unknown_slot24()
{
    unknown_130 = 0;
    for (int y = 0; y < 512; y++) {
        for (int x = 0; x < 512; x++) {
            int index = y * 512 + x;
            if (index < Cells.Length() && Cells[index] != 0) {
                new (Cells[index]) CellClass;
            }
        }
    }
}
