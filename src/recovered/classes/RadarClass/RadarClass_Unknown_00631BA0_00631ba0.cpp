// Point2D RadarClass::Unknown_00631BA0(Point2D const &position, bool clip) (0x00631BA0)
// The radar pixel of a lepton position (256 leptons per cell): rotated onto
// the diamond, scaled by the zoom (+0x1484), and kept inside the radar
// rectangle's size when clip is set.
#include "shared/radar.hpp"
// @ref __ftol=0077f110
// @ref __real@4@3ff78000000000000000=007a87fc

Point2D RadarClass::Unknown_00631BA0(Point2D const &position, bool clip)
{
    int px = position.X;
    int py = position.Y;
    int x = (int)((unknown_148c * 256 - py + px) * unknown_1484 * (1.0f / 256.0f));
    int y = (int)((py - unknown_1494 * 256 + px) * unknown_1484 * (1.0f / 256.0f));
    if (clip) {
        if (x < 0) {
            x = 0;
        }
        if (x >= unknown_1498.Width) {
            x = unknown_1498.Width - 1;
        }
        if (y < 0) {
            y = 0;
        }
        if (y >= unknown_1498.Height) {
            y = unknown_1498.Height - 1;
        }
    }
    return Point2D(x, y);
}
