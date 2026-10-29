// bool MSBitPrintAnim::Unknown_Slot4(Surface *surface, Rect *dirty) (0x005AE560, slot 4)
// Prints the text clipped to TextRect with the bitmap font and reports
// TextRect as the area to refresh; done once unknown_30 is set.
#include "shared/ms_anim.hpp"
// @ref ?Print_432490@unknown_bit_printer_84e9d0@@QAEXPAVunknown_bit_font_84e9e8@@PAVSurface@@PBGHHHHHHH@Z=00432490
// @ref ?Set_Clip_431460@unknown_bit_font_84e9e8@@QAEXPBURECT@@@Z=00431460
// @ref ?unknown_bit_font_84e9e8_ptr@@3PAVunknown_bit_font_84e9e8@@A=0084e9e8
// @ref ?unknown_bit_printer_84e9d0_ptr@@3PAVunknown_bit_printer_84e9d0@@A=0084e9d0

bool MSBitPrintAnim::Unknown_Slot4(Surface *surface, Rect *dirty)
{
    if (unknown_bit_printer_84e9d0_ptr != 0 && unknown_bit_font_84e9e8_ptr != 0) {
        RECT box;
        box.left = TextRect.X;
        box.top = TextRect.Y;
        box.right = TextRect.X + TextRect.Width - 1;
        box.bottom = TextRect.Height + TextRect.Y - 1;
        unknown_bit_font_84e9e8_ptr->Set_Clip_431460(&box);
        int unknown8 = unknown_31 != 0;
        unknown_bit_printer_84e9d0_ptr->Print_432490(unknown_bit_font_84e9e8_ptr, surface, Text.Get(), TextRect.X,
                                                     TextRect.Y, TextRect.Width, TextRect.Height, unknown8, 0, 0);
    }
    *dirty = TextRect;
    return !unknown_30;
}
