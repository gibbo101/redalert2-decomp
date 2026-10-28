// void MSFont::Print_Char(Surface *surface, unsigned short ch, int x, int y, int style, int unknown6) (0x005B43D0)
// Draws one glyph (frame (c - '!') * 3 + style) with its left edge at x;
// spaces and control characters draw nothing. Character 0xB0 is reported
// to the debug log first.
#include "shared/msfont.hpp"
// @ref ??_C@_08KGPM@Denzil?$CB?6?$AA@=007e5ddc

void MSFont::Print_Char(Surface *surface, unsigned short ch, int x, int y, int style, int unknown6)
{
    char c = (char)ch;
    if (c == 0xB0) {
        Debug_Printf("Denzil!\n");
    }
    CharToOemBuffA(&c, &c, 1);
    if ((unsigned char)c > ' ') {
        int index;
        if ((unsigned char)c - '!' <= 0) {
            index = 0;
        } else if ((unsigned char)c - '!' >= 0xD8) {
            index = 0xD8;
        } else {
            index = (unsigned char)c - '!';
        }
        int frame = index * 3;
        Point2D offset(0, 0);
        Rect rect = Shape->Get_Frame_Rect(frame + 2);
        Point2D point(x - rect.X, y);
        CC_Draw_Shape(surface, Drawer, Shape, frame + style, point, surface->Get_Rect(),
                      0x400, 0, 0, 0, 1000, 0, 0, offset);
    }
}
