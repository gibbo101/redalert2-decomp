// void MSVQAnim::Draw(Surface *surface, Rect const *clip) (0x005AE230, slot 5)
// Copies the movie area from the background surface onto `surface` (while
// playing) unless it lies outside `clip`.
#include "shared/ms_anim.hpp"

void MSVQAnim::Draw(Surface *surface, Rect const *clip)
{
    if (Movie != 0 && !Done) {
        if (clip != 0) {
            Rect area = clip->Intersect(Movie->Dest);
            if (!area.Is_Valid()) {
                return;
            }
        }
        surface->Copy_From(Movie->Source, *unknown_surface_839958, Movie->Dest, false, true);
    }
}
