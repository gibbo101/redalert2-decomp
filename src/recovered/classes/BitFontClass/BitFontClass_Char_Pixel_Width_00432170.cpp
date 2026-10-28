// int BitFontClass::Char_Pixel_Width(wchar_t character) const (0x00432170)
// The glyph's width byte (0 without a glyph).
#include "shared/text_print.hpp"

int BitFontClass::Char_Pixel_Width(wchar_t character) const
{
    unsigned char *glyph = Glyph_Data(character);
    if (glyph) {
        return *glyph;
    }
    return 0;
}
