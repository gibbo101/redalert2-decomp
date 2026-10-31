// int __fastcall Unknown_00562930(Cell const &cell) (0x00562930)
// Whether the overlay of a cell (of the global Map) is in 0x4A..0x65.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8

int __fastcall Unknown_00562930(Cell const &cell)
{
    int overlay = Map[cell].OverlayIndex;
    return overlay >= 0x4a && overlay <= 0x65;
}
