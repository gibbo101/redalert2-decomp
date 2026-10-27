// int __fastcall Unknown_0055EB70(Cell const &cell) (0x0055EB70)
// Flags from the overlays of the cells at X - 1 and X + 1 of a cell (of the
// global Map): the right neighbour's overlay 0xD1, 0xD3, 0xD5 or 0xE0 gives
// 1, 0xD4 or 0xE7 gives 2; the left one's 0xD2-0xD4 or 0xE2 adds 4, 0xD5 or
// 0xE7 adds 8.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8

int __fastcall Unknown_0055EB70(Cell const &cell)
{
    int left = Map[Cell(cell.X - 1, cell.Y)].OverlayIndex;
    int right = Map[Cell(cell.X + 1, cell.Y)].OverlayIndex;
    int flags = 0;
    switch (right) {
    case 0xD1:
    case 0xD3:
    case 0xD5:
    case 0xE0:
        flags = 1;
        break;
    case 0xD4:
    case 0xE7:
        flags = 2;
        break;
    }
    switch (left) {
    case 0xD2:
    case 0xD3:
    case 0xD4:
    case 0xE2:
        flags |= 4;
        break;
    case 0xD5:
    case 0xE7:
        flags |= 8;
        break;
    }
    return flags;
}
