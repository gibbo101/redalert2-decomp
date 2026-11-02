// int __fastcall Unknown_0055DB90(Cell const &cell) (0x0055DB90)
// Flags from the overlays of the cells at Y - 1 and Y + 1 of a cell (of the
// global Map): the upper one's overlay gives 1 or 2, the lower one's adds
// 4 or 8.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8

int __fastcall Unknown_0055DB90(Cell const &cell)
{
    int up = Map[cell + Cell(0, -1)].OverlayIndex;
    int down = Map[cell + Cell(0, 1)].OverlayIndex;
    int flags = 0;
    switch (up) {
    case 0x57:
    case 0x59:
    case 0x5B:
    case 0x61:
        flags = 1;
        break;
    case 0x5A:
    case 0x65:
        flags = 2;
        break;
    }
    switch (down) {
    case 0x58:
    case 0x59:
    case 0x5A:
    case 0x63:
        flags |= 4;
        break;
    case 0x5B:
    case 0x65:
        flags |= 8;
        break;
    }
    return flags;
}
