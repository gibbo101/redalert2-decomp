// Cache drawing bounds for the current coordinate and tactical view position.
#include "shared/building.hpp"
#include "shared/tactical.hpp"
// @ref ?unknown_tactical_83996c@@3PAVTactical@@A=0083996c
// @ref ?Coord_To_Pixel@Tactical@@=006a29d0
// @ref ?unknown_func_45e290@BuildingTypeClass@@=0045e290
inline Rect Offset_Draw_Bounds(Rect const &bounds,Point2D const &pixel) { Point2D origin(bounds.X,bounds.Y); Point2D shifted=Point_Sum(origin,pixel); return Rect(shifted.X,shifted.Y,bounds.Width,bounds.Height); }
Rect BuildingClass::unknown_slot73()
{
    CoordStruct position=unknown_slot42();
    Point2D view=unknown_tactical_83996c->unknown_b0;
    Rect result;
    if(position==unknown_51c && view==unknown_528) {
        result=unknown_50c;
    } else {
        Point2D pixel;
        unknown_tactical_83996c->Coord_To_Pixel(position,pixel);
        result=Offset_Draw_Bounds(Type->unknown_func_45e290(),pixel);
        unknown_51c=position;
        unknown_528=view;
        unknown_50c=result;
    }
    return result;
}
