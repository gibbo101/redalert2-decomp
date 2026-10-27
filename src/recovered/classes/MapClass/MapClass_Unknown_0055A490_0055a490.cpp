// CellClass *MapClass::Unknown_0055A490() (0x0055A490)
// The next cell of the walk 0x0055A550 started: the walk follows diagonal
// rows (X up, Y down, 511 slots back in Cells per step); at a row's end the
// current X and Y are swapped and one of them stepped on by the parity of
// X - width + Y - 1, starting a row one or two cells shorter than the map
// width. Returns the cell of the slot it was at.
#include "shared/map.hpp"

CellClass *MapClass::Unknown_0055A490()
{
    CellClass **slot = unknown_114;
    if (unknown_110 != 0) {
        unknown_108++;
        unknown_10c--;
        unknown_110--;
        unknown_114 = slot - 511;
    } else {
        int temp = unknown_108;
        unknown_108 = unknown_10c;
        unknown_10c = temp;
        if ((unknown_108 - MapSize.Width + unknown_10c - 1) & 1) {
            unknown_10c++;
            unknown_110 = MapSize.Width - 1;
        } else {
            unknown_108++;
            unknown_110 = MapSize.Width - 2;
        }
        unknown_114 = &Cells[(unknown_10c << 9) + unknown_108];
    }
    return *slot;
}
