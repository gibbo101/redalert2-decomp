// bool MapClass::Unknown_0054AAB0(Cell const &cell) (0x0054AAB0)
// Whether a cell lies inside the map's diamond: X + Y beyond the map
// width (+0xF0) and up to width + 2 * height (+0xF4), X - Y and Y - X
// below the width.
#include "shared/map.hpp"

bool MapClass::Unknown_0054AAB0(Cell const &cell)
{
    int x = cell.X;
    int y = cell.Y;
    if (x + y > MapSize.Width && x - y < MapSize.Width && y - x < MapSize.Width &&
        x + y <= MapSize.Width + MapSize.Height * 2) {
        return true;
    }
    return false;
}
