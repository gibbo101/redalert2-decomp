// void MSBitPrintAnim::Draw(Surface *surface, Rect const *clip) (0x005AE620, slot 5)
// Prints the text with the bitmap font, clipped to clip (TextRect when 0).
#include "shared/ms_anim.hpp"
// @ref ?Print_432490@unknown_bit_printer_84e9d0@@QAEXPAVunknown_bit_font_84e9e8@@PAVSurface@@PBGHHHHHHH@Z=00432490
// @ref ?Set_Clip_431460@unknown_bit_font_84e9e8@@QAEXPBURECT@@@Z=00431460
// @ref ?unknown_bit_font_84e9e8_ptr@@3PAVunknown_bit_font_84e9e8@@A=0084e9e8
// @ref ?unknown_bit_printer_84e9d0_ptr@@3PAVunknown_bit_printer_84e9d0@@A=0084e9d0

void MSBitPrintAnim::Draw(Surface *surface, Rect const *clip)
{
    if (unknown_bit_printer_84e9d0_ptr != 0 && unknown_bit_font_84e9e8_ptr != 0) {
        if (clip == 0) {
            clip = &TextRect;
        }
        RECT box;
        box.left = clip->X;
        box.top = clip->Y;
        box.right = clip->X + clip->Width - 1;
        box.bottom = clip->Height + clip->Y - 1;
        unknown_bit_font_84e9e8_ptr->Set_Clip_431460(&box);
        int unknown8 = unknown_31 != 0;
        unknown_bit_printer_84e9d0_ptr->Print_432490(unknown_bit_font_84e9e8_ptr, surface, Text.Get(), TextRect.X,
                                                     TextRect.Y, TextRect.Width, TextRect.Height, unknown8, 0, 0);
    }
}
