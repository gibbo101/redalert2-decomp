// BitTextClass::~BitTextClass() (0x004322D0)
// Releases the game font.
#include "shared/text_print.hpp"

BitTextClass::~BitTextClass()
{
    BitFontClass *font = BitFont;
    delete font;
    if (font == BitFont) {
        BitFont = 0;
    }
}
