// void DisplayClass::Unknown_0049CF00(Cell const &cell) (0x0049CF00)
// Unmaps a cell on the map for layer 0: a visible cell loses its visible
// and fully-shrouded bits (+0x12C bits 3 and 4) and is redrawn, and its
// neighbours lose the fully-shrouded bit and are redrawn.
#include "shared/display.hpp"
#include "shared/map_cell.hpp"
#include "shared/tactical.hpp"
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?Unknown_0054AAB0@MapClass@@QAE_NABVCell@@@Z=0054aab0
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Unknown_006AADD0@Tactical@@QAEXPAVCellClass@@@Z=006aadd0

void DisplayClass::Unknown_0049CF00(Cell const &cell)
{
    if (!Unknown_0054AAB0(cell)) {
        return;
    }
    CellClass &target = (*this)[cell];
    if (!(target.unknown_12c & 8)) {
        return;
    }
    target.unknown_12c &= ~0x18;
    unknown_tactical_83996c->Unknown_006AADD0(&target);
    for (int facing = 0; facing < 8; facing++) {
        Cell adjacent = Adjacent_Cell(cell, facing);
        CellClass &next = (*this)[adjacent];
        if (adjacent != cell) {
            next.unknown_12c &= ~0x10;
            unknown_tactical_83996c->Unknown_006AADD0(&next);
        }
    }
}
