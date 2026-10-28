// Intersect (0x0041FDF0): the inline definition of the free Intersect declared
// in shared/rect.hpp, for the units that expand it.
//
// An inline header function in the original: the kept copy is out of line at
// 0x0041FDF0. DSurface::Copy_From (0x004AAFD0), the MSAnim Draw slots, the
// BinkClass globals unit and ObjectClass Draw_Clipped expand it (a second
// expansion in one caller makes its zero rectangle with the out-of-line Rect
// constructor 0x0042BCD0). Each unit includes it in the file of its first
// expanding function: functions earlier in a unit that call it out of line
// (MSShapeAnim::Draw 0x005ACBB0) must not see it. xsurface.cpp never sees it:
// with the definition visible, XSurface::Draw_Line (0x00773980) expands it,
// while the original calls 0x0041FDF0 there (as do Plot_Line and Clip_Blit_Rects).
#ifndef RA2_SHARED_RECT_INTERSECT_HPP
#define RA2_SHARED_RECT_INTERSECT_HPP

#include "shared/rect.hpp"

inline Rect __fastcall Intersect(Rect const &rect1, Rect const &rect2, int *x, int *y)
{
    Rect empty(0, 0, 0, 0);
    Rect result = rect2;
    if (!rect1.Is_Valid() || !rect2.Is_Valid()) {
        return empty;
    }
    if (result.X < rect1.X) {
        result.Width += result.X - rect1.X;
        result.X = rect1.X;
    }
    if (result.Width < 1) {
        return empty;
    }
    if (result.Y < rect1.Y) {
        result.Height += result.Y - rect1.Y;
        result.Y = rect1.Y;
    }
    if (result.Height < 1) {
        return empty;
    }
    if (result.X + result.Width > rect1.X + rect1.Width) {
        result.Width = rect1.X - result.X + rect1.Width;
    }
    if (result.Width < 1) {
        return empty;
    }
    if (result.Y + result.Height > rect1.Y + rect1.Height) {
        result.Height = rect1.Y + rect1.Height - result.Y;
    }
    if (result.Height < 1) {
        return empty;
    }
    if (x != 0) {
        *x += rect2.X - result.X;
    }
    if (y != 0) {
        *y += rect2.Y - result.Y;
    }
    return result;
}

#endif
