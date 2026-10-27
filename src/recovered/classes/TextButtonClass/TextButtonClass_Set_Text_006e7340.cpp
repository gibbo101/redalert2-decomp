// void TextButtonClass::Set_Text(wchar_t const *text, bool resize) (0x006E7340, slot 34)
// Changes the text; resize refits the button to it.
#include "shared/gadget.hpp"

void TextButtonClass::Set_Text(wchar_t const *text, bool resize)
{
    String = text;
    Flag_To_Redraw();
    if (resize && String != 0) {
        BitFontClass *font = Font_For_Style(PrintFlags);
        Width = font->String_Pixel_Width(String, 0) + 8;
        Height = font->Height + 2;
    }
}
