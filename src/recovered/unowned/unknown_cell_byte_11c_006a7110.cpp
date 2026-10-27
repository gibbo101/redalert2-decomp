// int __stdcall unknown_cell_byte_11c(CoordStruct const &coord) -- 0x006A7110
// Purpose: the byte at +0x11C of the cell at coord (0x00548000).
// Assumptions: what the cell byte holds is unknown.
#include "shared/coord.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ??AMapClass@@QAEAAVCellClass@@ABUCoordStruct@@@Z=00548000

struct UnknownCell_006a7110 {
    char unknown_000[0x11C];
    unsigned char unknown_11c;              // +0x11C
};

int __stdcall unknown_cell_byte_11c(CoordStruct const &coord)
{
    return ((UnknownCell_006a7110 *)&Map[coord])->unknown_11c;
}
