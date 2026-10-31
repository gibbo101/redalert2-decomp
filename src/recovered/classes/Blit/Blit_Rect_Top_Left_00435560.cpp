// RectPoint2D Rect::Top_Left() const (0x00435560)
// The rectangle's top left corner.
#include "shared/rect.hpp"

RectPoint2D Rect::Top_Left() const
{
    return RectPoint2D(X, Y);
}
