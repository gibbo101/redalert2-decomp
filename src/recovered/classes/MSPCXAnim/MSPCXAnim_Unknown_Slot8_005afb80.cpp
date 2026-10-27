// void MSPCXAnim::Unknown_Slot8(int unknown1) (0x005AFB80, slot 8)
// Copies the picture into the background again (while active).
#include "shared/ms_anim.hpp"

void MSPCXAnim::Unknown_Slot8(int unknown1)
{
    if (Image != 0 && unknown_0C) {
        Background->Copy_From(PCXRect, *Image, Image->Get_Rect(), false, true);
    }
}
