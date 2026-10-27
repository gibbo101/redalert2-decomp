// Rect RadarClass::Unknown_00631470(Cell const &cell) (0x00631470)
// A cell's place on the zoomed radar: the diamond position scaled by the
// zoom at +0x1484 and offset by the radar rectangle's origin (+0x1498); one
// pixel wider at the right edge.
#include "shared/radar.hpp"
// @ref __ftol=0077f110

Rect RadarClass::Unknown_00631470(Cell const &cell)
{
    int cx = cell.X;
    int cy = cell.Y;
    int x = (int)((unknown_148c - cy + cx) * unknown_1484 + unknown_1498.X);
    int y = (int)((cy - unknown_1494 + cx) * unknown_1484 + unknown_1498.Y);
    if (x == unknown_1498.X - 1) {
        x++;
    }
    return Rect(x, y, 1, 1);
}
