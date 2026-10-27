// void EditClass::Draw_Text(wchar_t const *text) (0x004B2C90, slot 37)
// Prints the text inside the box (bright, 0x2000, while it has the focus)
// in colour scheme Color, clipped to the inner width; with the focus and
// room for another character, an underscore cursor follows the text.
#include "shared/gadget.hpp"
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?Fancy_Clip_Text_Print@@YI?AUPoint2D@@PBGPAVSurface@@PBVRect@@PAU1@PAVColorScheme@@IIIPBH@Z=00497e80
// @ref ?Font_For_Style@@YIPAVBitFontClass@@H@Z=00497a50
// @ref ?String_Pixel_Width@BitFontClass@@QBEHPBGH@Z=00431690
// @ref _wcslen=00783605
// @ref ??_C@_13IKBE@?$AA_?$AA?$AA@=007d642c

void EditClass::Draw_Text(wchar_t const *text)
{
    unsigned flags = Has_Focus() ? 0x2000 : 0;
    Point2D point(X + 1, Y + 1);
    Fancy_Clip_Text_Print(text, unknown_surface_83995c, &unknown_surface_83995c->Get_Rect(), &point,
                          ColorSchemes[Color], 0, TextFlags | flags, Width - 2, 0);

    BitFontClass *font = Font_For_Style(TextFlags);
    if (Has_Focus() && wcslen(text) < (unsigned)MaxLength
        && font->String_Pixel_Width(text, 0) + font->String_Pixel_Width(L"_", 0) < Width - 2) {
        point.X = X + 1 + font->String_Pixel_Width(text, 0);
        point.Y = Y + 1;
        Fancy_Clip_Text_Print(L"_", unknown_surface_83995c, &unknown_surface_83995c->Get_Rect(), &point,
                              ColorSchemes[Color], 0, TextFlags | flags, (unsigned)-1, 0);
    }
}
