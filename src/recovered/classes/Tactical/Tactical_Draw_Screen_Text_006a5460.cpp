// void Tactical::Draw_Screen_Text(wchar_t const *text) (0x006A5460): unless images are being reloaded, draws the
// caption over the middle of the tactical view on a DirectDraw surface: frame unknown_a4 of GRFXTXT.SHP when one is
// set, else the text in white, centred in the bitmap font (TibSun Tactical::Draw_Screen_Text).
// The unit keeps no empty-rectangle copy of its own: the shape helpers fall back on its header static rectangle.
#define SHAPE_FILE_EMPTY_RECT unknown_static_rect
#include "shared/unknown_static_rect.hpp"
#include "shared/tactical.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/surface.hpp"
#include "shared/palette.hpp"
#include "shared/text_print.hpp"
#include "shared/hicolor.hpp"
#include "shared/tag_rect.hpp"
#include "shared/msfont.hpp"
// @ref ?unknown_rect_839630@@3VRect@@A=00839630

void Tactical::Draw_Screen_Text(wchar_t const *text)
{
    if (unknown_flag_a40d13) {
        return;
    }
    if ((text == 0 || !wcslen(text)) && unknown_a4 == -1) {
        return;
    }
    if (unknown_surface_839964->Is_Direct_Draw()) {
        int frame = unknown_a4;
        if (frame != -1 && unknown_grfxtxt_drawer_a41678 != 0 && unknown_grfxtxt_shape_a41674 != 0
            && ((ShapeFileStruct const *)unknown_grfxtxt_shape_a41674)->FrameCount > frame) {
            ShapeFileStruct const *shape = (ShapeFileStruct const *)unknown_grfxtxt_shape_a41674;
            Point2D point((unknown_rect_839630.Width - shape->Width) / 2, (unknown_rect_839630.Height - shape->Height) / 2);
            CC_Draw_Shape(unknown_surface_839964, unknown_grfxtxt_drawer_a41678, shape, frame, point,
                unknown_rect_839630, 0, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
            return;
        }
        if (text != 0 && wcslen(text) > 0) {
            BitFontClass *font = BitFont;
            Rect rect = unknown_rect_839630;
            unsigned short color = Build_Hicolor_Pixel(255, 255, 255);
            int width;
            int height;
            font->Get_Text_Area(text, &width, &height, rect.Width);
            int x = (rect.Width - width) / 2 + rect.X;
            int y = rect.Y + (rect.Height - height) / 2;
            tagRECT box;
            box.left = rect.X;
            box.top = rect.Y;
            box.right = rect.X + rect.Width;
            box.bottom = rect.Height + rect.Y;
            font->Set_Clipping(true);
            font->Set_Clip_Box(&box);
            font->Set_Color(color);
            BitText->Print(font, unknown_surface_839964, text, x, y, 0, 0);
        }
    }
}
