// Point2D Point2D::operator-(Point2D const &point) const (0x0047D040):
// member-wise difference (out of line in the Cell.cpp unit).
#include "shared/rect.hpp"

Point2D Point2D::operator-(Point2D const &point) const
{
    return Point2D(X - point.X, Y - point.Y);
}
