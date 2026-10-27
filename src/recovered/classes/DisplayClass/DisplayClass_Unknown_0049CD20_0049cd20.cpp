// void DisplayClass::Unknown_0049CD20() (0x0049CD20)
// Re-maps the map: marks every mapped cell that is not fully shrouded
// (+0x140 bit 6), runs 0x0049E110 (false, true), then maps each marked cell
// again through 0x0049CDB0, clearing the mark.
#include "shared/display.hpp"
#include "shared/map_cell.hpp"
// @ref ?Unknown_0055A550@MapClass@@QAEXXZ=0055a550
// @ref ?Unknown_0055A490@MapClass@@QAEPAVCellClass@@XZ=0055a490
// @ref ?Unknown_0049E110@DisplayClass@@QAEX_N0@Z=0049e110
// @ref ?Unknown_0049CDB0@DisplayClass@@QAEXABVCell@@@Z=0049cdb0

void DisplayClass::Unknown_0049CD20()
{
    Unknown_0055A550();
    for (CellClass *cell = Unknown_0055A490(); cell != 0; cell = Unknown_0055A490()) {
        if (!(cell->unknown_140 & 1) && (cell->unknown_140 & 2)) {
            cell->unknown_140 |= 0x40;
        }
    }
    Unknown_0049E110(false, true);
    Unknown_0055A550();
    for (CellClass *marked = Unknown_0055A490(); marked != 0; marked = Unknown_0055A490()) {
        if (marked->unknown_140 & 0x40) {
            marked->unknown_140 &= ~0x40;
            Cell where = marked->MapCoords;
            Unknown_0049CDB0(where);
        }
    }
}
