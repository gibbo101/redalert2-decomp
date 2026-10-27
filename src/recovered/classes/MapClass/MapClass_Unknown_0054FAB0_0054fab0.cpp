// int MapClass::Unknown_0054FAB0(Cell const &cell) (0x0054FAB0)
// The cell's index in the +0x64 array: Y * (width + height + 1) + X,
// clamped to 0 .. +0x68 - 1.
#include "shared/map.hpp"

int MapClass::Unknown_0054FAB0(Cell const &cell)
{
    int index = (MapSize.Height + 1 + MapSize.Width) * cell.Y + cell.X;
    if (index < 0) {
        return 0;
    }
    if (index >= unknown_68) {
        index = unknown_68 - 1;
    }
    return index;
}
