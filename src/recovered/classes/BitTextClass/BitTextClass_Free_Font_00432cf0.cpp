// void BitTextClass::Free_Font(BitFontClass *font) (0x00432CF0): deletes a font; BitFont is cleared when it was
// the game font. No callers.
#include "shared/text_print.hpp"

void BitTextClass::Free_Font(BitFontClass *font)
{
    delete font;
    if (font == BitFont) {
        BitFont = 0;
    }
}
