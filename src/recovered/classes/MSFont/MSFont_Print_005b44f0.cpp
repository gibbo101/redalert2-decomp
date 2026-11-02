// void MSFont::Print(Surface *surface, unsigned short const *text, int x, int y, int style) (0x005B44F0)
// Draws a string glyph by glyph; '\n' returns to x on the next line.
#include "shared/msfont.hpp"

void MSFont::Print(Surface *surface, unsigned short const *text, int x, int y, int style)
{
    int xpos = x;
    while (*text != 0) {
        if (*text == '\n') {
            xpos = x;
            y += Height;
        } else {
            if (*text > ' ') {
                char c = (char)*text;
                char oem;
                CharToOemBuffA(&c, &oem, 1);
                int index = (0 >= oem - 33u) ? 0 : oem - 33u;
                index = (216 <= index) ? 216 : index;
                int frame = index * 3;
                Point2D offset(0, 0);
                Rect rect = Shape->Get_Frame_Rect(frame + 2);
                Point2D point(xpos - rect.X, y);
                CC_Draw_Shape(surface, Drawer, Shape, frame + style, point, surface->Get_Rect(),
                              0x400, 0, 0, 0, 1000, 0, 0, offset);
            }
            xpos += Char_Width(*text);
        }
        text++;
    }
}
