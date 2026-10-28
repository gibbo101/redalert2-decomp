// bool MapClass::Unknown_0055A740(CellClass *cell, bool flag) (0x0055A740)
// The test of 0x0055A660 for a cell object (its own height bytes when flag
// is set).
#include "shared/map.hpp"

bool MapClass::Unknown_0055A740(CellClass *cell, bool flag)
{
    int height = 0;
    int x = cell->MapCoords.X;
    int y = cell->MapCoords.Y;
    if (flag) {
        height = cell->unknown_11b;
        if (cell->unknown_11c && x + y < MapSize.Width + MapLocalSize.Y * 2 + 4 + height) {
            height++;
        }
    }
    if (x + y > MapSize.Width + MapLocalSize.Y * 2 + height &&
        x + y <= MapSize.Width + (MapLocalSize.Height + MapLocalSize.Y) * 2 + 2 + height &&
        x - y < (MapLocalSize.Width + MapLocalSize.X) * 2 - MapSize.Width &&
        y - x < MapSize.Width - MapLocalSize.X * 2) {
        return true;
    }
    return false;
}
