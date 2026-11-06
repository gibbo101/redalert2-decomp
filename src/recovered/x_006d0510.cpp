// TechnoClass 0x006D0510.
#include "shared/techno.hpp"
#include "shared/tactical.hpp"
#include "shared/tool_tip.hpp"
#include "shared/gadget.hpp"
#include "shared/hicolor.hpp"
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/convert.hpp"
// @ref ?unknown_dash_7f7130@@3QB_NB=007f7130
// @ref ??0Rect@@QAE@ABURectPoint2D@@HH@Z=00453e40
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0
// @ref ??HRectPoint2D@@QBE?BU0@ABU0@@Z=00435540
extern bool const unknown_dash_7f7130[];
// TibSun's TRect::operator+ with a corner: the rectangle moved by a point.
inline Rect Moved_Rect(Rect const &rect, Point2D const &point)
{
    return Rect(rect.Top_Left()+(RectPoint2D const &)point,rect.Width,rect.Height);
}
void TechnoClass::unknown_6d0510(CoordStruct from, CoordStruct to, RGBClass color, int arg8, int arg9)
{
    Point2D start;
    Point2D end;
    unknown_tactical_83996c->Coord_To_Pixel(from,start);
    unknown_tactical_83996c->Coord_To_Pixel(to,end);
    start.Y+=unknown_rect_839630.Y;
    end.Y+=unknown_rect_839630.Y;
    Point2D shadow_start=start;
    shadow_start.Y+=1;
    Point2D shadow_end=end;
    shadow_end.Y+=1;
    char shadow=(char)arg9;
    if (shadow) {
        int black=unknown_drawer_8323c4->Convert(0);
        unknown_surface_839964->Fill_Rect(unknown_rect_839630.Intersect(Moved_Rect(Rect(-2,-2,3,3),shadow_start)),black);
        black=unknown_drawer_8323c4->Convert(0);
        unknown_surface_839964->Fill_Rect(unknown_rect_839630.Intersect(Moved_Rect(Rect(-2,-2,3,3),shadow_end)),black);
    }
    Rect clip=unknown_rect_839630;
    if (shadow && Clip_Line(shadow_start,shadow_end,clip)) {
        unknown_surface_839964->Draw_Line(shadow_start,shadow_end,unknown_drawer_8323c4->Convert(0));
    }
    int pixel=((color.Red>>unknown_shift_852fbc)<<unknown_shift_852fb8)|((color.Blue>>unknown_shift_852fc4)<<unknown_shift_852fc0)|((color.Green>>unknown_shift_852fcc)<<unknown_shift_852fc8);
    unknown_surface_839964->Fill_Rect(unknown_rect_839630.Intersect(Moved_Rect(Rect(-2,-2,3,3),start)),pixel);
    unknown_surface_839964->Fill_Rect(unknown_rect_839630.Intersect(Moved_Rect(Rect(-2,-2,3,3),end)),pixel);
    if ((char)arg8) {
        int offset=(0x7fffffff-Frame)%15;
        if (Clip_Line(start,end,clip)) {
            unknown_surface_839964->Draw_Dashed_Line_Depth_Masked(start,end,pixel,unknown_dash_7f7130,offset,false);
        }
    } else {
        if (Clip_Line(start,end,clip)) {
            unknown_surface_839964->Draw_Line(start,end,pixel);
        }
    }
}
