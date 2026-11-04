// Compute the fire coordinate from the voxel barrel transform and turret pixel offset.
#include "shared/building.hpp"
#include "shared/matrix3d.hpp"
#include "shared/tactical.hpp"
// @ref ?unknown_453900@BuildingClass@@=00453900
// @ref ??D@YI?AUVector3@@ABVMatrix3D@@ABU0@@Z=00591380
// @ref ?Unknown_006A2900@Tactical@@=006a2900
static inline CoordStruct Add_Pixel_Offset(CoordStruct &coord,Point2D const &point)
{ coord.X+=point.X; coord.Y+=point.Y; return coord; }
CoordStruct BuildingClass::unknown_44ed60(int weapon, bool previous)
{
    WeaponTypeClass *weapon_type=unknown_slot231(weapon)->WeaponType;
    int burst;
    if(previous) {
        if(unknown_310==0) burst=weapon_type->Burst-1;
        else burst=unknown_310-1;
    } else burst=unknown_310;
    int lateral;
    if(burst==0) lateral=Type->VoxelBarrelOffsetToBarrelEnd.Y;
    else if(burst==1) lateral=-Type->VoxelBarrelOffsetToBarrelEnd.Y;
    else lateral=0;
    Vector3 offset((float)Type->VoxelBarrelOffsetToBarrelEnd.X,(float)lateral,(float)Type->VoxelBarrelOffsetToBarrelEnd.Z);
    Vector3 point=unknown_453900()*offset;
    int x=(int)point.X;
    int y=(int)-point.Y;
    int z=(int)point.Z;
    CoordStruct delta(x,y,z);
    CoordStruct result=unknown_slot42()+delta;
    Point2D pixel(Type->Anims[9].Offset.X,Type->Anims[9].Offset.Y);
    return Add_Pixel_Offset(result,unknown_tactical_83996c->Unknown_006A2900(pixel));
}
