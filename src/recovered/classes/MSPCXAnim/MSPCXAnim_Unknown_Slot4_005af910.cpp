// bool MSPCXAnim::Unknown_Slot4(Surface *surface, Rect *dirty) (0x005AF910, slot 4)
// The first time (while active): copies the picture into the background,
// draws it onto `surface`, reports its rectangle and redraws every other
// animation of the list inside it. True once shown unless unknown_28.
#include "shared/ms_anim.hpp"

bool MSPCXAnim::Unknown_Slot4(Surface *surface, Rect *dirty)
{
    if (!Done) {
        if (unknown_0C) {
            if (Image != 0) {
                Background->Copy_From(PCXRect, *Image, Image->Get_Rect(), false, true);
                Draw(surface, 0);
                Rect area = PCXRect;
                *dirty = area;
                int index = Anims->ID(this);
                for (int i = 0; i < Anims->Count(); i++) {
                    if (i != index) {
                        (*Anims)[i]->Draw(surface, &area);
                    }
                }
            }
            Done = true;
        }
    }
    return Done && !unknown_28;
}
