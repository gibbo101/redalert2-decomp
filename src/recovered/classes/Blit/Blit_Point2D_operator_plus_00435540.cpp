// RectPoint2D const RectPoint2D::operator+(RectPoint2D const &point) const (0x00435540)
// Component-wise sum. Out of line: callers (Prep_For_Blit, RLE_Blit) call it.
#include "shared/rect.hpp"

RectPoint2D const RectPoint2D::operator+(RectPoint2D const &point) const
{
    return RectPoint2D(X + point.X, Y + point.Y);
}
