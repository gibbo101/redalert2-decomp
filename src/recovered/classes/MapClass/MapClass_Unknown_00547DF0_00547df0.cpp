// Point2D MapClass::Unknown_00547DF0(Point2D const &point) (0x00547DF0)
// Unknown_00547DB0 relative to MapLocalSize's origin.
#include "shared/map.hpp"

Point2D MapClass::Unknown_00547DF0(Point2D const &point)
{
    Point2D offset(MapLocalSize.X, MapLocalSize.Y);
    Point2D result = Unknown_00547DB0(point);
    return Point2D(result.X - offset.X, result.Y - offset.Y);
}
