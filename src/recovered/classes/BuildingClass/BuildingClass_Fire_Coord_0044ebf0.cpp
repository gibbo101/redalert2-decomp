// Resolve a building fire coordinate from garrison, pixel, or voxel-barrel offsets.
#include "shared/building.hpp"
#include "shared/tactical.hpp"
// @ref ?unknown_slot181@TechnoClass@@=006c1a70
// @ref ?unknown_44ed60@BuildingClass@@=0044ed60
// @ref ?Unknown_006A2900@Tactical@@=006a2900
static inline CoordStruct Add_Pixel_Offset(CoordStruct &coord,UnknownPoint2D const &point);
CoordStruct BuildingClass::unknown_slot181(int weapon)
{
    if(Type->CanBeOccupied && unknown_554.Count()>0) {
        CoordStruct offset=Projected_Coord_0043bbd0(unknown_tactical_83996c->Unknown_006A2900(Type->MuzzleFlash[unknown_56c]));
        return unknown_slot42()+offset;
    } else {
        Point2D const &pixel=Type->PrimaryFirePixelOffset;
        if(Fire_Pixels_Differ_0043bbd0(pixel,Point2D(65535,65535))) {
            CoordStruct offset=Projected_Coord_0043bbd0(unknown_tactical_83996c->Unknown_006A2900((UnknownPoint2D const &)pixel));
            return unknown_slot42()+offset;
        }
        if(Type->BarrelAnimIsVoxel) return unknown_44ed60(weapon,false);
        CoordStruct coord=TechnoClass::unknown_slot181(weapon);
        if(Type->TurretAnimIsVoxel) {
            UnknownPoint2D turret(Type->Anims[9].Offset.X,Type->Anims[9].Offset.Y);
            coord=Add_Pixel_Offset(coord,unknown_tactical_83996c->Unknown_006A2900(turret));
        }
        return coord;
    }
}
