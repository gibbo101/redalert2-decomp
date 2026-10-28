// void BitFontClass::Set_Surface(Surface *surface) (0x004320B0)
// Draws into the locked surface; an unset clip box becomes the whole
// surface, a set one is clipped to it.
#include "shared/text_print.hpp"
// @ref ?Intersect_Rect@BitFontClass@@QAE_NPAUtagRECT@@PBU2@1@Z=00432000

void BitFontClass::Set_Surface(Surface *surface)
{
    Buffer = surface->Lock();
    Pitch = (unsigned)surface->Stride() >> 1;
    tagRECT rect;
    rect.left = 0;
    rect.top = 0;
    rect.right = surface->Get_Width() - 1;
    rect.bottom = surface->Get_Height() - 1;
    if (!(ClipBox.right | ClipBox.bottom | ClipBox.top | ClipBox.left)) {
        ClipBox.left = rect.left;
        ClipBox.top = rect.top;
        ClipBox.right = rect.right;
        ClipBox.bottom = rect.bottom;
    } else {
        Intersect_Rect(&ClipBox, &ClipBox, &rect);
    }
}
