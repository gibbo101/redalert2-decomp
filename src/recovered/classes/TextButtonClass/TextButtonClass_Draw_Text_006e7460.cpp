// void TextButtonClass::Draw_Text(wchar_t const *text) (0x006E7460, slot 37)
// Prints the text centred on the button (one pixel down) in the box colour
// scheme (scheme 0 when the index is out of range): disabled plain, pressed
// or on with 0x6000, otherwise with 0x5000, added to the button's print
// flags and centring (0x100).
#include "shared/gadget.hpp"
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?unknown_scheme_index_4cefc0@@YAHXZ=004cefc0
// @ref ?Fancy_Text_Print@@YI?AUPoint2D@@PBGPAVSurface@@PBVRect@@PAU1@PAVColorScheme@@IIH@Z=00497990

void TextButtonClass::Draw_Text(wchar_t const *text)
{
    int index = unknown_scheme_index_4cefc0();
    if (String != 0) {
        unsigned flags;
        if (IsDisabled) {
            flags = 0;
        } else if (IsPressed || IsOn) {
            flags = 0x6000;
        } else {
            flags = 0x5000;
        }
        if (ColorSchemes.Count() != 0) {
            if (index <= 0 || index >= ColorSchemes.Count()) {
                index = 0;
            }
            ColorScheme *scheme = ColorSchemes[index];
            if (scheme != 0) {
                Point2D point(X + (Width >> 1) - 1, Y + 1);
                Fancy_Text_Print(text, unknown_surface_83995c, &unknown_surface_83995c->Get_Rect(), &point,
                                 scheme, 0, PrintFlags | flags | 0x100, 1);
            }
        }
    }
}
