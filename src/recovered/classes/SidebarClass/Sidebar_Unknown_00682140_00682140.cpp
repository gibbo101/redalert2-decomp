// void __fastcall Unknown_00682140(wchar_t const *text, Point2D const &point, Rect const &window, int width) (0x00682140)
// With captions on (0x008373C0), prints text on the sidebar surface in the
// "DarkRed" scheme's base colour, clipped to window and wrapped to width,
// with its last line on the font's line at point.
#include "shared/sidebar.hpp"
#include "shared/tool_tip.hpp"
#include "shared/text_print.hpp"
#include "shared/color_scheme.hpp"
#include "shared/hicolor.hpp"
#include "shared/progress_screen.hpp"
// @ref ??_C@_07MMLF@DarkRed?$AA@=007ebfd0
// @ref ?unknown_flag_8373c0@@3_NA=008373c0
// @ref ?BitFont@@3PAVBitFontClass@@A=0084e9e8
// @ref ?BitText@@3PAVBitTextClass@@A=0084e9d0
// @ref ?unknown_color_scheme_663d30@@YIPAVColorScheme@@PBDH@Z=00663d30
// @ref ?To_RGB@HSVClass@@QBE?AVRGBClass@@XZ=004ff050
// @ref ?Set_Clipping@BitFontClass@@QAEEE@Z=00431450
// @ref ?Set_Clip_Box@BitFontClass@@QAEXPBUtagRECT@@@Z=00431460
// @ref ?Set_Color@BitFontClass@@QAEGG@Z=00431430
// @ref ?Get_Text_Area@BitFontClass@@QAEXPBGPAH1H@Z=004314b0
// @ref ?Unknown_00432490@BitTextClass@@QAEXPAVBitFontClass@@PAVSurface@@PBGHHHHHHH@Z=00432490
// @ref ?unknown_surface_839948@@3PAVSurface@@A=00839948
// @ref ??_C@_07HBEO@DarkRed?$AA@=007ebfd0


void __fastcall Unknown_00682140(wchar_t const *text, Point2D const &point, Rect const &window, int width)
{
    if (unknown_flag_8373c0 && text != 0) {
        Point2D xy = point;
        BitFontClass *font = BitFont;
        ColorScheme *scheme = unknown_color_scheme_663d30("DarkRed", 1);
        RGBClass color = scheme->BaseColor.To_RGB();
        unsigned pixel = ((color.Red >> unknown_shift_852fbc) << unknown_shift_852fb8)
            | ((color.Green >> unknown_shift_852fcc) << unknown_shift_852fc8)
            | ((color.Blue >> unknown_shift_852fc4) << unknown_shift_852fc0);
        tagRECT box;
        box.left = window.X;
        box.top = window.Y;
        box.right = window.X + window.Width;
        box.bottom = window.Y + window.Height;
        font->Set_Clipping(1);
        font->Set_Clip_Box(&box);
        font->Set_Color(pixel);
        int text_width;
        int text_height;
        font->Get_Text_Area(text, &text_width, &text_height, width);
        xy.Y += font->Height - text_height;
        BitText->Print_Box(font, unknown_surface_839948, text, xy.X, xy.Y, width, 0, 0, 0, 0);
    }
}
