// TPoint2D TPoint2D::operator+(TPoint2D const &point) const (0x00435540)
// Component-wise sum. Out of line: callers (Prep_For_Blit, RLE_Blit) call it.
#include "shared/rect.hpp"

TPoint2D TPoint2D::operator+(TPoint2D const &point) const
{
    return TPoint2D(X + point.X, Y + point.Y);
}
