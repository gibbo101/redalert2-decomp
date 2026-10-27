// int MapClass::Unknown_0056A8A0() (0x0056A8A0)
// While +0x144 is still 13 or more, lowers it to the +0x11B value of every
// cell (0x0056A870, expanded inline); returns +0x144.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"

int MapClass::Unknown_0056A8A0()
{
    if (unknown_144 >= 13) {
        int count = Cells.Length();
        for (int index = 0; index < count; index++) {
            CellClass *cell = Cells[index];
            if (cell != 0) {
                Unknown_0056A870(cell->unknown_11b);
            }
        }
    }
    return unknown_144;
}
