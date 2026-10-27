// bool MSVQAnim::Unknown_Slot4(Surface *surface, Rect *dirty) (0x005ADFE0, slot 4)
// Shows each new movie frame and, when the movie ends, the picture; every
// other animation of the list is redrawn over the area. Without a movie the
// picture is shown once. True when done unless unknown_2c.
#include "shared/ms_anim.hpp"
// @ref ?VQA_Movie_Unknown_005A15F0@@YI_NPAVVQAMovie@@PA_N@Z=005a15f0

bool MSVQAnim::Unknown_Slot4(Surface *surface, Rect *dirty)
{
    int index;
    int i;
    if (Movie != 0) {
        bool finished = false;
        if (!Done) {
            if (VQA_Movie_Unknown_005A15F0(Movie, &finished) == true) {
                Draw(surface, 0);
                *dirty = Movie->Dest;
                index = Anims->ID(this);
                for (i = 0; i < Anims->Count(); i++) {
                    if (i != index) {
                        (*Anims)[i]->Draw(surface, &Movie->Dest);
                    }
                }
            }
            if (finished == true && Image != 0) {
                Target->Copy_From(Movie->Source, *Image, Image->Get_Rect(), false, true);
                Draw(surface, 0);
                *dirty = Movie->Dest;
                index = Anims->ID(this);
                for (i = 0; i < Anims->Count(); i++) {
                    if (i != index) {
                        (*Anims)[i]->Draw(surface, &Movie->Dest);
                    }
                }
            }
            if (finished) {
                Done = finished;
            }
        }
    } else {
        if (!Done && Image != 0) {
            Rect rect = Image->Get_Rect();
            Target->Copy_From(rect, *Image, rect, false, true);
            Draw(surface, 0);
            *dirty = rect;
            index = Anims->ID(this);
            for (i = 0; i < Anims->Count(); i++) {
                if (i != index) {
                    (*Anims)[i]->Draw(surface, &rect);
                }
            }
        }
        Done = true;
    }
    return Done && !unknown_2c;
}
