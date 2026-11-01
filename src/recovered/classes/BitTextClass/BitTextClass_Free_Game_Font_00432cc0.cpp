// void BitTextClass::Free_Game_Font() (0x00432CC0): releases the game font, as the destructor. No callers.
#include "shared/text_print.hpp"

void BitTextClass::Free_Game_Font()
{
    BitFontClass *font = BitFont;
    delete font;
    if (font == BitFont) {
        BitFont = 0;
    }
}
