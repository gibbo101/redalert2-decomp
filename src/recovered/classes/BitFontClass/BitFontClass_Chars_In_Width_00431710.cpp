// BitFontClass::Chars_In_Width (0x00431710): how many characters of string fit in width pixels (tabs
// to the tab width; CR/LF take no room), at most count (0: no limit); with wrap, a line break ends the
// run and a cut inside a word moves back to the word's start (unless the word fills the run).
#include "shared/text_print.hpp"

int BitFontClass::Chars_In_Width(wchar_t const *string, int width, int count, int wrap) const
{
    int x = 0;
    int chars = 0;
    if (Data == 0 || string == 0) {
        return 0;
    }
    wchar_t character = *string;
    while (character != 0) {
        switch (character) {
        case 9:
            x += unknown_28;
            x -= x % unknown_28;
            break;
        case 10:
        case 13:
            break;
        default: {
            unsigned char *glyph = Glyph_Data(character);
            if (glyph != 0 || (glyph = (unsigned char *)unknown_08) != 0) {
                x += unknown_2c + *glyph;
            }
            break;
        }
        }
        chars++;
        if (x > width) {
            chars--;
            if (wrap != 0 && character > 0x20) {
                string--;
                int back = chars;
                while (back != 0 && *string > 0x20) {
                    back--;
                    string--;
                }
                if (back != 0) {
                    chars = back;
                }
            }
            break;
        }
        if (count != 0 && chars == count) {
            break;
        }
        if (wrap != 0 && (character == 13 || character == 10)) {
            break;
        }
        character = *++string;
    }
    return chars;
}
