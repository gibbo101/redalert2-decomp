// void MSBinkAnim::Draw(Surface *surface, Rect const *clip) (0x005ADAF0, slot 5)
// Copies the movie rectangle from the background surface onto `surface`.
// The overlap with `clip` is computed but not used.
#include "shared/ms_anim.hpp"
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0
// @ref ??0Rect@@QAE@HHHH@Z=0042bcd0
#include "shared/rect_intersect.hpp"

void MSBinkAnim::Draw(Surface *surface, Rect const *clip)
{
    if (clip != 0) {
        Rect area = clip->Intersect(MovieRect);
    }
    surface->Copy_From(MovieRect, *unknown_surface_839958, MovieRect, false, true);
}
