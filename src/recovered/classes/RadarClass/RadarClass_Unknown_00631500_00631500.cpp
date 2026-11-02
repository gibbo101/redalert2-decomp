// Cell RadarClass::Unknown_00631500(Point2D const &point) (0x00631500)
// The cell under a radar pixel: the pixel unscaled by the zoom (+0x1484),
// moved back by the diamond offsets and rotated, rounding to nearest.
#include "shared/radar.hpp"
// @ref __ftol=0077f110
// @ref __real@4@3ffe8000000000000000=0079dd80
// @ref __real@8@3ffe8000000000000000=0079a728

Cell RadarClass::Unknown_00631500(Point2D const &point)
{
    float x = point.X / unknown_1484 - unknown_148c;
    float y = point.Y / unknown_1484 + unknown_1494;
    Cell cell;
    float sum = y;
    sum += x;
    cell.X = (short)(sum * 0.5f + 0.5);
    cell.Y = (short)((y - x) * 0.5f + 0.5);
    return cell;
}
