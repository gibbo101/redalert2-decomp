// void BitFontClass::unknown_431ec0() (0x00431EC0)
// Keeps an inverted copy of the 'X' glyph in unknown_08.
#include "shared/text_print.hpp"
// @ref _malloc=00782630

// Never expanded inline in its unit (both callers call it).
#pragma auto_inline(off)
void BitFontClass::unknown_431ec0()
{
    unknown_08 = malloc(Data->unknown_08 * Data->Width + 2);
    unsigned char *glyph = Glyph_Data('X');
    if (glyph) {
        *(unsigned char *)unknown_08 = *glyph++;
        unsigned char *out = (unsigned char *)unknown_08 + 1;
        for (unsigned y = 0; y < (unsigned)Data->unknown_08; y++) {
            for (unsigned x = 0; x < (unsigned)Data->Width; x++) {
                *out++ = ~*glyph++;
            }
        }
    }
}
#pragma auto_inline(on)
