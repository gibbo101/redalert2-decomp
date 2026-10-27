// void StaticButtonClass::Draw_Text(wchar_t const *text) (0x00698A10, slot 35)
// Prints text at the gadget, centred or right-aligned by Style, in the
// gadgets' colour scheme.
#include "shared/gadget.hpp"

void StaticButtonClass::Draw_Text(wchar_t const *text)
{
    if (Text != 0) {
        int x = X;
        if (Style & 0x100) {
            x += Width / 2;
        }
        if (Style & 0x200) {
            x += Width - 1;
        }
        Fancy_Text_Printf(text, unknown_surface_83995c, &unknown_surface_83995c->Get_Rect(), &Point2D(x, Y),
                          ColorSchemes[Gadget_Color_Scheme()], 0, Style);

    }
}
