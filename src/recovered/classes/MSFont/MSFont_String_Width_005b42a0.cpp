// int MSFont::String_Width(unsigned short const *text) (0x005B42A0)
// Pixel width of the widest line of a multi-line string.
#include "shared/msfont.hpp"

int MSFont::String_Width(unsigned short const *text)
{
    int widest = 0;
    if (text != 0) {
        do {
            int width = 0;
            while (*text != 0 && *text != '\n') {
                width += Char_Width(*text++);
            }
            if (*text == '\n') {
                text++;
            }
            if (width > widest) {
                widest = width;
            }
        } while (*text != 0);
    }
    return widest;
}
