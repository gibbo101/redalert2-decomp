// Point2D MapClass::Unknown_00547D70(Point2D const &point) (0x00547D70)
// Unknown_00547D40 of point moved by MapLocalSize's origin.
#include "shared/map.hpp"

Point2D MapClass::Unknown_00547D70(Point2D const &point)
{
    Point2D offset(MapLocalSize.X, MapLocalSize.Y);
    return Unknown_00547D40(Point2D(point.X + offset.X, point.Y + offset.Y));
}
