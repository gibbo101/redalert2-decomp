// Point2D Point2D::operator+(Point2D const &point) const (0x00435540)
// Component-wise sum. Out of line: callers (Prep_For_Blit, RLE_Blit) call it.
#include "shared/rect.hpp"

Point2D Point2D::operator+(Point2D const &point) const
{
    return Point2D(X + point.X, Y + point.Y);
}
