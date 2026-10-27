// bool MSBinkAnim::Unknown_Slot4(Surface *surface, Rect *dirty) (0x005ADA20, slot 4)
// Shows each new movie frame: draws it, reports the movie rectangle and
// redraws every other animation of the list inside it. True once the movie
// finished unless unknown_38.
#include "shared/ms_anim.hpp"
// @ref ?Unknown_00430800@BinkClass@@QAE_NXZ=00430800

bool MSBinkAnim::Unknown_Slot4(Surface *surface, Rect *dirty)
{
    if (surface == 0) {
        return false;
    }
    if (Movie == 0) {
        return true;
    }
    if (!Movie->Unknown_00430420() && Movie->Unknown_00430800()) {
        Draw(surface, 0);
        *dirty = MovieRect;
        int index = Anims->ID(this);
        for (int i = 0; i < Anims->Count(); i++) {
            if (i != index) {
                (*Anims)[i]->Draw(surface, &MovieRect);
            }
        }
    }
    return Movie->Unknown_00430420() && !unknown_38;
}
