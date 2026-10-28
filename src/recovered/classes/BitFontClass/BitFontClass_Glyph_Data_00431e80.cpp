// unsigned char *BitFontClass::Glyph_Data(wchar_t character) const (0x00431E80)
// The character's glyph (its width byte, then the bitmap), or null.
#include "shared/text_print.hpp"

unsigned char *BitFontClass::Glyph_Data(wchar_t character) const
{
    unsigned char *glyph = 0;
    if (Data) {
        unsigned index = Data->Map[character];
        if (index) {
            glyph = Data->Glyphs + Data->GlyphSize * (index - 1);
        }
    }
    return glyph;
}
