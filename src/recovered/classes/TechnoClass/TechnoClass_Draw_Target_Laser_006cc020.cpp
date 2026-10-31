// Draw a dashed targeting line with a three-pixel marker at each end.
#include "shared/techno.hpp"
#include "shared/tactical.hpp"
#include "shared/convert.hpp"
#include "shared/surface.hpp"
extern Rect unknown_rect_839630;
// @ref _?pattern@?1??unknown_6cc020@TechnoClass@@QAEXXZ@4PA_NA=007f7114
// @ref ??0Rect@@QAE@ABURectPoint2D@@HH@Z=00453e40
// @ref ?Intersect@@YI?AVRect@@ABV1@0PAH1@Z=0041fdf0
// Reference rectangle/point operations, with their ordinary C++ copy lifetimes.
inline Rect::Rect(RectPoint2D const &point,int width,int height):X(point.X),Y(point.Y),Width(width),Height(height) {}
inline RectPoint2D Rect::Top_Left() const { return RectPoint2D(X,Y); }
inline RectPoint2D RectPoint2D::operator-(RectPoint2D const &point) const { return RectPoint2D(X-point.X,Y-point.Y); }
inline Rect Rect::operator-(RectPoint2D const &point) const { return Rect(Top_Left()-point,Width,Height); }
static inline Rect Target_Laser_Rect(Point2D const &point)
{
    Point2D offset=point-Point2D(2,2);
    return Rect(RectPoint2D(offset.X,offset.Y),3,3);
}
void TechnoClass::unknown_6cc020()
{
    static bool pattern[16]={true,false,true,false,true,false,true,false,true,false,true,false,true,false,true,false};
    if(unknown_228) {
        CoordStruct source=unknown_slot181(0);
        CoordStruct target=unknown_6d65b0();
        Point2D start;
        Point2D end;
        unknown_tactical_83996c->Coord_To_Pixel(source,start);
        unknown_tactical_83996c->Coord_To_Pixel(target,end);
        start.Y+=unknown_rect_839630.Y;
        end.Y+=unknown_rect_839630.Y;
        unknown_surface_83995c->Fill_Rect(unknown_rect_839630.Intersect(Rect(RectPoint2D(start.X,start.Y),3,3)-RectPoint2D(2,2)),unknown_drawer_8323c4->Convert(8));
        unknown_surface_83995c->Fill_Rect(unknown_rect_839630.Intersect(Target_Laser_Rect(end)),unknown_drawer_8323c4->Convert(8));
        Rect clip=unknown_rect_839630;
        if(Clip_Line(start,end,clip)) {
            unknown_surface_83995c->Draw_Dashed_Line(start,end,unknown_drawer_8323c4->Convert(8),pattern,7*Frame%16);
        }
    }
}
