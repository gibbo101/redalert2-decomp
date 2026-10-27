// void TextButtonClass::Draw_Background() (0x006E7390, slot 36)
// Unless the button is bordered: an outline one pixel outside it (palette
// index 12 of the box colour scheme) when it has a black border, then a
// filled box: disabled raised (3), pressed down (0) or raised (1).
#include "shared/gadget.hpp"
// @ref ?ColorSchemes@@3V?$DynamicVectorClass@PAVColorScheme@@@@A=00ab6ef8
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?unknown_scheme_index_4cefc0@@YAHXZ=004cefc0
// @ref ?Draw_Box@@YIXABVRect@@H_N@Z=004973d0

void TextButtonClass::Draw_Background()
{
    if (!IsBordered) {
        if (IsBlackBorder) {
            unknown_surface_83995c->Draw_Rect(Rect(X - 1, Y - 1, X + Width + 2, Y + Height + 2),
                                              ColorSchemes[unknown_scheme_index_4cefc0()]->Converter->Convert(12));
        }
        int style;
        if (IsDisabled) {
            style = 3;
        } else {
            style = !IsPressed;
        }
        Draw_Box(Rect(X, Y, Width, Height), style, true);
    }
}
