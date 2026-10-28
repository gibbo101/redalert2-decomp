// Rect Rect::operator-(TPoint2D const &point) const (0x0047D000): the
// rectangle moved back by point (out of line in the Cell.cpp unit).
#include "shared/rect.hpp"

Rect Rect::operator-(TPoint2D const &point) const
{
    TPoint2D origin = TPoint2D(X, Y) - point;
    return Rect(origin.X, origin.Y, Width, Height);
}
