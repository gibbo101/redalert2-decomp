// int __fastcall Unknown_0055ECA0(Cell const &cell) (0x0055ECA0)
// Flags from the overlays of the cells at Y - 1 and Y + 1 of a cell (of the
// global Map): the upper one's overlay gives 1 or 2, the lower one's adds
// 4 or 8.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8

int __fastcall Unknown_0055ECA0(Cell const &cell)
{
    int up = Map[Cell(cell.X, cell.Y - 1)].OverlayIndex;
    int down = Map[Cell(cell.X, cell.Y + 1)].OverlayIndex;
    int flags = 0;
    switch (up) {
    case 0xDA:
    case 0xDC:
    case 0xDE:
    case 0xE4:
        flags = 1;
        break;
    case 0xDD:
    case 0xE8:
        flags = 2;
        break;
    }
    switch (down) {
    case 0xDB:
    case 0xDC:
    case 0xDD:
    case 0xE6:
        flags |= 4;
        break;
    case 0xDE:
    case 0xE8:
        flags |= 8;
        break;
    }
    return flags;
}
