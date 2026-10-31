// void DisplayClass::Unknown_0049CDB0(Cell const &cell) (0x0049CDB0)
// Unmaps a cell on the map for layer 1: clears its mapped bits, sets its
// layer-1 frame to 0xFE and redraws it when visible. Each neighbour the
// tactical view reports as -2 while its frame is not 0xFE is unmapped in
// turn; one that is fully shrouded or whose frame changed takes the new
// frame (when both are at least -1/0) and is marked mapped. A cell that was
// mapped then runs 0x0047BC80.
#include "shared/display.hpp"
#include "shared/map_cell.hpp"
#include "shared/tactical.hpp"
// @ref ??AMapClass@@QAEAAVCellClass@@ABVCell@@@Z=00548070
// @ref ?Unknown_0054AAB0@MapClass@@QAE_NABVCell@@@Z=0054aab0
// @ref ?AdjacentCell@@3QBVCell@@B=00851a70
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Unknown_006AADD0@Tactical@@QAEXPAVCellClass@@@Z=006aadd0
// @ref ?Cell_Shadow@Tactical@@QAEHABVCell@@_N@Z=006a8d40
// @ref ?unknown_47bc80@CellClass@@QAEXXZ=0047bc80
// @ref ?Unknown_0049CDB0@DisplayClass@@QAEXABVCell@@@Z=0049cdb0

void DisplayClass::Unknown_0049CDB0(Cell const &cell)
{
    if (!Unknown_0054AAB0(cell)) {
        return;
    }
    CellClass &target = (*this)[cell];
    bool mapped = false;
    if (target.unknown_140 & 3) {
        mapped = true;
    }
    target.unknown_140 &= ~3;
    target.unknown_121 = 0xFE;
    if (target.unknown_12c & 8) {
        unknown_tactical_83996c->Unknown_006AADD0(&target);
    }
    for (int facing = 0; facing < 8; facing++) {
        Cell adjacent = Adjacent_Cell(cell, facing);
        CellClass &next = (*this)[adjacent];
        Cell where = next.MapCoords;
        int frame = unknown_tactical_83996c->Cell_Shadow(where, 1);
        if (frame == -2 && (char)next.unknown_121 != (char)frame) {
            Unknown_0049CDB0(adjacent);
        } else if ((next.unknown_140 & 1) || frame != (char)next.unknown_121) {
            if (frame >= 0 && (char)next.unknown_121 >= -1) {
                next.unknown_121 = frame;
                next.unknown_140 = (next.unknown_140 & ~1) | 2;
                unknown_tactical_83996c->Unknown_006AADD0(&next);
            }
        }
    }
    if (mapped) {
        target.unknown_47bc80();
    }
}
