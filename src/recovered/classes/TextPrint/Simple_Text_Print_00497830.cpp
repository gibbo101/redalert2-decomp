// Point2D Simple_Text_Print(wchar_t const *text, Surface *surface, Rect const *clip, Point2D *xy, unsigned fore, unsigned back, unsigned flags, int unknown8) (0x00497830)
// Prints text at xy inside clip in colour fore (flag 0x100 centres, 0x200
// right-aligns; 0x8000 puts a translucent black box behind it, 0x400 an
// opaque one); returns where it was drawn.
#include "shared/text_print.hpp"
// @ref ?Get_Text_Area@BitFontClass@@QAEXPBGPAH1H@Z=004314b0
// @ref ?Set_Clipping@BitFontClass@@QAEEE@Z=00431450
// @ref ?Set_Clip_Box@BitFontClass@@QAEXPBUtagRECT@@@Z=00431460
// @ref ?Set_Color@BitFontClass@@QAEGG@Z=00431430
// @ref ?Print@BitTextClass@@QAEXPAVBitFontClass@@PAVSurface@@PBGHHHH@Z=00432350
// @ref ?BitText@@3PAVBitTextClass@@A=0084e9d0

struct tagRECT {
    long left;
    long top;
    long right;
    long bottom;
};

Point2D __fastcall Simple_Text_Print(wchar_t const *text, Surface *surface, Rect const *clip, Point2D *xy,
                                     unsigned fore, unsigned back, unsigned flags, int unknown8)
{
    BitFontClass *font = BitFont;
    int x = clip->X + xy->X;
    int y = clip->Y + xy->Y;
    int width;
    int height;
    font->Get_Text_Area(text, &width, &height, clip->Width);

    if (flags & 0x100) {
        x -= width / 2;
    } else if (flags & 0x200) {
        x -= width;
    }

    if (flags & 0x8000) {
        RGBClass shadow(0, 0, 0);
        Rect box(x - 1, y - 1, width + 2, height + 2);
        surface->Unknown_Slot7((int)&box, (int)&shadow, 0x3C);
    } else if (flags & 0x400) {
        surface->Fill_Rect(Rect(x - 1, y - 1, width + 2, height + 2), 0);
    }

    tagRECT box;
    box.left = clip->X;
    box.top = clip->Y;
    box.right = clip->X + clip->Width;
    box.bottom = clip->Y + clip->Height;
    font->Set_Clipping(1);
    font->Set_Clip_Box(&box);
    font->Set_Color(fore);
    BitText->Print(font, surface, text, x, y, 0, 0);
    return Point2D(x, y);
}
