// void ProgressScreenClass::Draw_Bar(Point2D xy, double fraction, Surface *surface, ColorScheme *scheme) (0x0061F8F0)
// Draws the shape's first frame cut to fraction of its width, through the
// scheme's drawer (DarkRed's colours and the GUI drawer without a scheme,
// Drawer when set), with an outline in the scheme's base colour when
// unknown_71 is set.
#include "shared/progress_screen.hpp"
#include "shared/surface.hpp"
#include "shared/palette.hpp"
#include "shared/color_scheme.hpp"
#include "shared/hsv_class.hpp"
#include "shared/hicolor.hpp"
#include "shared/gadget.hpp"
// @ref ??_C@_07MMLF@DarkRed?$AA@=007ebfd0

void ProgressScreenClass::Draw_Bar(Point2D xy, double fraction, Surface *surface, ColorScheme *scheme)
{
    Rect rect = Shape->Get_Frame_Rect(0);
    rect.X = xy.X + 3;
    rect.Y = xy.Y + 3;
    Rect outline = rect;
    Unknown_Rect_Shrink_006F1B00(&outline, -3);
    ConvertClass *drawer;
    if (scheme == 0) {
        scheme = unknown_color_scheme_663d30("DarkRed", 1);
        drawer = unknown_drawer_8323c4;
    } else {
        drawer = scheme->Converter;
    }
    if (Drawer != 0) {
        drawer = Drawer;
    }
    if (unknown_71) {
        RGBClass color = scheme->BaseColor.To_RGB();
        surface->Draw_Rect(outline, Build_Hicolor_Pixel(color.Red, color.Green, color.Blue));
    }
    Rect bar = rect;
    bar.Width = rect.Width * fraction;
    CC_Draw_Shape(surface, drawer, Shape, 0, Point2D(0, 0), bar, 0x400, 0, 0, 0, 1000, 0, 0, Point2D(0, 0));
}
