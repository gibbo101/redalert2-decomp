// Rect RadarClass::Unknown_00631400(Cell const &cell) (0x00631400)
// A cell's place on the radar's diamond map: two pixels wide (one at the
// left and right edges of the local map), one high.
#include "shared/radar.hpp"

Rect RadarClass::Unknown_00631400(Cell const &cell)
{
    int cx = cell.X;
    int cy = cell.Y;
    int x = unknown_148c - cy + cx;
    int y = cy - unknown_1494 + cx;
    int width = 2;
    if (x == -1) {
        x = 0;
        width = 1;
    } else if (x == MapLocalSize.Width * 2 - 1) {
        width = 1;
    }
    return Rect(x, y, width, 1);
}
