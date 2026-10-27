// void MSBinkAnim::Draw(Surface *surface, Rect const *clip) (0x005ADAF0, slot 5)
// Copies the movie rectangle from the background surface onto `surface`.
// The overlap with `clip` is computed but not used.
#include "shared/ms_anim.hpp"
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0
// @ref ??0Rect@@QAE@HHHH@Z=0042bcd0

// Intersect (0x0041FDF0) is an inline header function in the original: its
// kept copy is out of line, and the Draw slots of this unit expand it through
// Rect::Intersect, with its zero rectangle through the out-of-line Rect
// constructor 0x0042BCD0. Defined here (the unit's first user) until
// shared/rect.hpp carries it; MSShapeAnim::Draw (0x005ACBB0), which calls it
// out of line, is left out of the unit for now.
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


void MSBinkAnim::Draw(Surface *surface, Rect const *clip)
{
    if (clip != 0) {
        Rect area = clip->Intersect(MovieRect);
    }
    surface->Copy_From(MovieRect, *unknown_surface_839958, MovieRect, false, true);
}
