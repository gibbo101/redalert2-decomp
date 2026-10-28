// void BitFontClass::unknown_431fa0() (0x00431FA0)
// One pixel taller, with the ideographic space (U+3000) twice as wide as the space.
#include "shared/text_print.hpp"

void BitFontClass::unknown_431fa0()
{
    if (Data) {
        Height++;
        unsigned char *space = Glyph_Data(' ');
        unsigned char *wide = Glyph_Data(0x3000);
        if (wide) {
            if (space) {
                *wide = *space << 1;
            } else {
                *wide = *(unsigned char *)Data;
            }
        }
    }
}
