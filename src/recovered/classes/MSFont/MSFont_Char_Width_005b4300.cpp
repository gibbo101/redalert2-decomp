// int MSFont::Char_Width(unsigned short ch) (0x005B4300)
// Advance of one character: 8 for a space, 0 for control characters, else
// the glyph frame width plus one.
#include "shared/msfont.hpp"
// @ref __imp__CharToOemBuffA@12=0079a4f4

int MSFont::Char_Width(unsigned short ch)
{
    char c = (char)ch;
    CharToOemBuffA(&c, &c, 1);
    if (c == ' ') {
        return 8;
    }
    if ((unsigned char)c > ' ') {
        int index;
        if ((unsigned char)c - '!' <= 0) {
            index = 0;
        } else if ((unsigned char)c - '!' >= 0xD8) {
            index = 0xD8;
        } else {
            index = (unsigned char)c - '!';
        }
        Rect rect = Shape->Get_Frame_Rect(index * 3 + 2);
        return rect.Width + 1;
    }
    return 0;
}
