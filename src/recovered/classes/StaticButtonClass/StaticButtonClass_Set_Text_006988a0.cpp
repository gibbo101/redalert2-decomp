// void StaticButtonClass::Set_Text(wchar_t const *text, bool resize) (0x006988A0, slot 33)
// Replaces the owned copy of the text and flags a redraw; with resize, the
// gadget takes the text's size in the style's font (after restoring the
// screen under it and discarding the saved area).
#include "shared/gadget.hpp"

void StaticButtonClass::Set_Text(wchar_t const *text, bool resize)
{
    if (Text != 0) {
        delete Text;
        Text = 0;
    }
    if (text != 0) {
        Text = new wchar_t[wcslen(text) + 1];
        if (Text != 0) {
            wcscpy(Text, text);
        }
    }
    Flag_To_Redraw();
    if (resize && Text != 0) {
        Draw_Background();
        BitFontClass *font = Font_For_Style(Style);
        Width = font->String_Pixel_Width(Text, 0);
        Height = font->Height;
        Background = Buffer();
    }
}
