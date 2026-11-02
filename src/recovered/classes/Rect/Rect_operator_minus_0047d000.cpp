// Rect Rect::operator-(RectPoint2D const &point) const (0x0047D000): the
// rectangle moved back by point (TibSun rect.h's form: the corner moved by the point; out of line in the
// Cell.cpp unit, which sees Top_Left and the corner constructor inline under RA2_RECT_CORNER_INLINE).
#include "shared/rect.hpp"

Rect Rect::operator-(RectPoint2D const &point) const
{
    return Rect(Top_Left() - point, Width, Height);
}
