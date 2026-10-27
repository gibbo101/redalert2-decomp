// Point2D MapClass::Unknown_00547DB0(Point2D const &point) (0x00547DB0)
// Inverse of Unknown_00547D40. No direct callers (inlined everywhere).
#include "shared/map.hpp"

Point2D MapClass::Unknown_00547DB0(Point2D const &point)
{
    int width = MapSize.Width;
    int x = (width & 1) ? point.X - point.Y + 1 : point.X - point.Y;
    return Point2D((x >> 1) + width / 2, point.Y - width + point.X);
}
