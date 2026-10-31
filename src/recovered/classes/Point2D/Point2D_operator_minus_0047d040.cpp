// RectPoint2D RectPoint2D::operator-(RectPoint2D const &point) const (0x0047D040):
// member-wise difference (out of line in the Cell.cpp unit).
#include "shared/rect.hpp"

RectPoint2D RectPoint2D::operator-(RectPoint2D const &point) const
{
    return RectPoint2D(X - point.X, Y - point.Y);
}
