// void MSFont::Text_Rect(unsigned short const *text, Rect &rect) (0x005B41F0)
// Bounding rectangle of a multi-line string: widest line plus Width, one
// Height per line; empty for a null or empty string.
#include "shared/msfont.hpp"
// @ref _wcslen=00783605

void MSFont::Text_Rect(unsigned short const *text, Rect &rect)
{
    int widest = 0;
    int width = 0;
    if (text != 0 && wcslen(text) != 0) {
        int height = Height;
        do {
            width = 0;
            while (*text != 0 && *text != '\n') {
                width += Char_Width(*text++);
            }
            if (width > widest) {
                widest = width;
            }
            if (*text == '\n') {
                text++;
                height += Height;
            }
        } while (*text != 0);
        int total = Width + widest;
        rect.Height = height;
        rect.Width = total;
        rect.X = 0;
        rect.Y = 0;
        return;
    }
    rect.X = width;
    rect.Y = width;
    rect.Width = width;
    rect.Height = width;
}
