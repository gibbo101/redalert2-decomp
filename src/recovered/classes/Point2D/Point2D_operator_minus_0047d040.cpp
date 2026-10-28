// TPoint2D TPoint2D::operator-(TPoint2D const &point) const (0x0047D040):
// member-wise difference (out of line in the Cell.cpp unit).
#include "shared/rect.hpp"

TPoint2D TPoint2D::operator-(TPoint2D const &point) const
{
    return TPoint2D(X - point.X, Y - point.Y);
}
