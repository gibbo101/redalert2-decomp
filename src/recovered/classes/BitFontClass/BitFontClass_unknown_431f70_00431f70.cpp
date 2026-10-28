// void BitFontClass::unknown_431f70() (0x00431F70)
// One pixel taller, with the space one pixel wider.
#include "shared/text_print.hpp"

void BitFontClass::unknown_431f70()
{
    if (Data) {
        Height++;
        (*Glyph_Data(' '))++;
    }
}
