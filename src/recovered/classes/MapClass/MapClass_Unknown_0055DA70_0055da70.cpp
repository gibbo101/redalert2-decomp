// int __fastcall Unknown_0055DA70(Cell const &cell) (0x0055DA70)
// Flags from the overlays of the cells at X - 1 and X + 1 of a cell (of the
// global Map): the right neighbour's overlay 0x4E, 0x50, 0x52 or 0x5D gives
// 1, 0x51 or 0x64 gives 2; the left one's 0x4F-0x51 or 0x5F adds 4, 0x52 or
// 0x64 adds 8.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8

int __fastcall Unknown_0055DA70(Cell const &cell)
{
    int left = Map[Cell(cell.X - 1, cell.Y)].OverlayIndex;
    int right = Map[Cell(cell.X + 1, cell.Y)].OverlayIndex;
    int flags = 0;
    switch (right) {
    case 0x4E:
    case 0x50:
    case 0x52:
    case 0x5D:
        flags = 1;
        break;
    case 0x51:
    case 0x64:
        flags = 2;
        break;
    }
    switch (left) {
    case 0x4F:
    case 0x50:
    case 0x51:
    case 0x5F:
        flags |= 4;
        break;
    case 0x52:
    case 0x64:
        flags |= 8;
        break;
    }
    return flags;
}
