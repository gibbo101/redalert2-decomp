// void MapClass::Unknown_0055A300() (0x0055A300)
// Refreshes the shroud drawing of every cell in two walks (0x0055A490): cells
// flagged +0x140 bit 0x20 lose their +0x12C bits 0x18 and +0x140 bits 0x23 and
// are redrawn; then each cell whose layer 0 shroud frame (0x006A8D40) changed
// takes it and is redrawn. A redrawn cell that is fully shrouded (frame 0xFE)
// reveals its nearby technos to the player (0x00568520).
#include "shared/map.hpp"
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_adjacent.hpp"

void MapClass::Unknown_0055A300()
{
    Unknown_0055A550();
    CellClass *cellptr = Unknown_0055A490();
    while (cellptr != 0) {
        if (cellptr->unknown_140 & 0x20) {
            cellptr->unknown_12c &= ~0x18;
            cellptr->unknown_140 &= ~0x23;
            cellptr->unknown_138 = true;
            unknown_tactical_83996c->Unknown_006AADD0(cellptr);
            if (cellptr->unknown_120 == 0xFE) {
                Map.Unknown_00568520(cellptr, unknown_player_a35db4, true);
            }
        }
        cellptr = Unknown_0055A490();
    }

    Unknown_0055A550();
    cellptr = Unknown_0055A490();
    while (cellptr != 0) {
        Cell cell = Coord_Cell(cellptr->Center_Coord());
        unsigned char frame = unknown_tactical_83996c->Cell_Shadow(cell, 0);
        if (frame != cellptr->unknown_120) {
            cellptr->unknown_120 = frame;
            cellptr->unknown_138 = true;
            unknown_tactical_83996c->Unknown_006AADD0(cellptr);
            if (cellptr->unknown_120 == 0xFE) {
                Map.Unknown_00568520(cellptr, unknown_player_a35db4, true);
            }
        }
        cellptr = Unknown_0055A490();
    }
}
