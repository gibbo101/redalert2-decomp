#define SHAPE_FILE_EMPTY_RECT unknown_score_empty_rect_ab6f20
#include "shared/score_font.hpp"
#include "shared/surface.hpp"
#include "shared/palette.hpp"
#include "shared/msfont.hpp"
// @ref ?CC_Draw_Shape@@YIXPAVSurface@@PAVConvertClass@@PBUShapeFileStruct@@HABUPoint2D@@ABVRect@@HHHHHHHU4@@Z=0049eea0
// @ref ?unknown_score_empty_rect_ab6f20@@3VRect@@B=00ab6f20

void ScoreFontClass::Print(Surface *surface, unsigned short const *string, int x, int y, int frame)
{
    while (*string != 0) {
        if (*string != ' ') {
            char c = (char)*string;
            char ch;
            CharToOemBuffA(&c, &ch, 1);
            // The unsigned lower choice preserves negative signed-byte offsets.
            int index = ((ch - '!') > 0U ? (ch - '!') : 0U);
            if (index >= 0xD8) {
                index = 0xD8;
            }
            CC_Draw_Shape(surface, Drawer, Image, index * 3 + frame, Point2D(x - Image->Get_Frame_Rect(index * 3 + 2).X, y),
                          surface->Get_Rect(), 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
        }
        x += Char_Pixel_Width(*string) + 1;
        string++;
    }
}
