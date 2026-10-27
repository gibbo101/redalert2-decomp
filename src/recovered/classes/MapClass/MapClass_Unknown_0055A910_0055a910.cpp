// CellClass *MapClass::Unknown_0055A910() (0x0055A910)
// Steps the walk over the local map rectangle kept in +0x118 (X) and +0x11C
// (Y): along a diagonal row (X up, Y down) and, past the rectangle's right
// edge, back to the start of the next row; returns the first cell it
// passes that is inside the local map (0x0055A660), or null below the
// rectangle's bottom.
#include "shared/map.hpp"
#include "shared/map_cell.hpp"
// @ref ?Unknown_0055A660@MapClass@@QAE_NABVCell@@_N@Z=0055a660
// @ref ?unknown_dummy_cell_a6f9f8@@3VCellClass@@A=00a6f9f8

CellClass *MapClass::Unknown_0055A910()
{
    while (unknown_118 + unknown_11c <= MapSize.Width + (MapLocalSize.Y + MapLocalSize.Height) * 2 + 12) {
        int x = unknown_118;
        int y = unknown_11c;
        Cell cell(x, y);
        if (x - y >= (MapLocalSize.X + MapLocalSize.Width) * 2 - MapSize.Width - 2) {
            bool odd = ((unknown_118 - MapSize.Width + unknown_11c - 1) & 1) == 1;
            int length = MapLocalSize.Width - (odd ? 2 : 1);
            unknown_118 -= length;
            unknown_11c += length;
            if (odd) {
                unknown_11c++;
            } else {
                unknown_118++;
            }
        } else {
            unknown_118++;
            unknown_11c--;
        }
        if (Unknown_0055A660(cell, true)) {
            return &(*this)[cell];
        }
    }
    return 0;
}
