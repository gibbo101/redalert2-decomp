// StaticButtonClass::StaticButtonClass(unsigned id, wchar_t const *text, int style, int x, int y, int w, int h) (0x00698760)
// A width or height of -1 is taken from the text in the style's font.
#include "shared/gadget.hpp"
#include "shared/blit.hpp"

StaticButtonClass::StaticButtonClass(unsigned id, wchar_t const *text, int style, int x, int y, int w, int h) :
    GadgetClass(x, y, w, h, 0, false),
    Text(0),
    Style(style)
{
    Set_Text(text);
    if (w == -1 || h == -1) {
        BitFontClass *font = Font_For_Style(Style);
        if (w == -1) {
            Width = font->String_Pixel_Width(Text, 0);
        }
        if (h == -1) {
            Height = font->Height;
        }
    }
}
