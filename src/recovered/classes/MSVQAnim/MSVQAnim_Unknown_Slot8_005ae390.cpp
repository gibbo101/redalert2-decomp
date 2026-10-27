// void MSVQAnim::Unknown_Slot8(int unknown1) (0x005AE390, slot 8)
// Copies the picture into the target again once the movie is done.
#include "shared/ms_anim.hpp"

void MSVQAnim::Unknown_Slot8(int unknown1)
{
    if (Done && Movie != 0 && Image != 0) {
        Target->Copy_From(Movie->Source, *Image, Image->Get_Rect(), false, true);
    }
}
