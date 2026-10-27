// Point2D Rect::Top_Left() const (0x00435560)
// The rectangle's top left corner.
#include "shared/rect.hpp"

Point2D Rect::Top_Left() const
{
    return Point2D(X, Y);
}
