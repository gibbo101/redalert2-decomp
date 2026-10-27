// int MapClass::Unknown_0054FAF0(Cell const &cell) (0x0054FAF0)
// The cell's index in the +0x64 array without clamping:
// Y * (width + height + 1) + X.
#include "shared/map.hpp"

int MapClass::Unknown_0054FAF0(Cell const &cell)
{
    return (MapSize.Height + 1 + MapSize.Width) * cell.Y + cell.X;
}
