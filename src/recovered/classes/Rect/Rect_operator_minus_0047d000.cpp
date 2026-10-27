// Rect Rect::operator-(Point2D const &point) const (0x0047D000): the
// rectangle moved back by point (out of line in the Cell.cpp unit).
#include "shared/rect.hpp"

Rect Rect::operator-(Point2D const &point) const
{
    Point2D origin = Point2D(X, Y) - point;
    return Rect(origin.X, origin.Y, Width, Height);
}
