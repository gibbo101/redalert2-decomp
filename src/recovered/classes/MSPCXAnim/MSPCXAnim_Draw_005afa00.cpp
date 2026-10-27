// void MSPCXAnim::Draw(Surface *surface, Rect const *clip) (0x005AFA00, slot 5)
// Copies the picture onto `surface` (while active and not yet shown) unless
// it lies outside `clip`.
#include "shared/ms_anim.hpp"
// @ref ??0Rect@@QAE@HHHH@Z=0042bcd0

void MSPCXAnim::Draw(Surface *surface, Rect const *clip)
{
    if (Image != 0 && !Done && unknown_0C) {
        if (clip != 0) {
            Rect area = clip->Intersect(PCXRect);
            if (!area.Is_Valid()) {
                return;
            }
        }
        surface->Copy_From(PCXRect, *Image, Image->Get_Rect(), false, true);
    }
}
