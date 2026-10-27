// Direction to a target after the building's fire-pixel or turret-animation offset.
#include "shared/building.hpp"
#include "shared/tactical.hpp"
#include "shared/fast_math.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Unknown_006A2900@Tactical@@=006a2900
// @ref ?Fast_Atan2@@=004ba600
inline CoordStruct Projected_Coord_0043bbd0(UnknownPoint2D const &point) { return CoordStruct(point.X,point.Y,0); }
inline UnknownFacingDir Direction_Between_0043bbd0(CoordStruct const &from,CoordStruct const &to)
{
    int target_x=to.X;
    return UnknownFacingDir((unsigned short)(int)((Fast_Atan2((double)from.Y-(double)to.Y,(double)target_x-(double)from.X)-1.5707963267948966)*-10430.060040584269));
}
static inline bool Fire_Pixels_Equal_0043bbd0(Point2D const &a,Point2D const &b)
{ return a.X==b.X && a.Y==b.Y; }
static inline bool Fire_Pixels_Differ_0043bbd0(Point2D const &a,Point2D const &b)
{ return !Fire_Pixels_Equal_0043bbd0(a,b); }
UnknownFacingDir BuildingClass::unknown_slot285(AbstractClass *target)
{
    CoordStruct offset=unknown_geometry_l;
    Point2D const &pixel=Type->PrimaryFirePixelOffset;
    if(Fire_Pixels_Differ_0043bbd0(pixel,Point2D(65535,65535))) {
        offset=Projected_Coord_0043bbd0(unknown_tactical_83996c->Unknown_006A2900((UnknownPoint2D const &)pixel));
    } else {
        UnknownPoint2D turret(Type->Anims[9].Offset.X,Type->Anims[9].Offset.Y);
        if(turret.X!=0 || turret.Y!=0) {
            offset=Projected_Coord_0043bbd0(unknown_tactical_83996c->Unknown_006A2900(turret));
        }
    }
    CoordStruct from=Center_Coord()+offset;
    return Direction_Between_0043bbd0(from,target->Center_Coord());
}
