// Point2D MapClass::Unknown_00547D40(Point2D const &point) (0x00547D40)
// Isometric transform: X gains half of Y (rounded up), Y becomes half of Y
// plus the map width less X. No direct callers (inlined everywhere).
#include "shared/map.hpp"

Point2D MapClass::Unknown_00547D40(Point2D const &point)
{
    return Point2D(((point.Y + 1) >> 1) + point.X, (point.Y >> 1) + MapSize.Width - point.X);
}
