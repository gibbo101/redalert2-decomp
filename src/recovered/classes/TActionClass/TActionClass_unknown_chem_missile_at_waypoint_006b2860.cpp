// bool TActionClass::unknown_chem_missile_at_waypoint(...) (0x006B2860)
// A ChemLauncher bullet (speed 20) aimed at the cell of waypoint +0x44 (ground height, raised on a bridge), launched at speed 100 from the ground centre of the cell Map 0x005689D0 picks near it; false when the bullet cannot be created.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/taction.hpp"
#include "shared/id_source.hpp"
#include "shared/bullet.hpp"
#include "shared/weapon_type.hpp"
#include "shared/map_cell.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?Get_Waypoint_Location@UnknownIDSource@@QBE?AVCell@@H@Z=00663180
// @ref ?Index_From_Name@WeaponTypeClass@@SIHPBD@Z=00733f30
// @ref ?Unknown_005689D0@MapClass@@QAE?AVCell@@ABV2@H@Z=005689d0
// @ref __real@8@4005c800000000000000=0079b7f0
// @ref _unknown_geometry_j=00abfdf8
// @ref ??_C@_0N@JEKJ@ChemLauncher?$AA@=007f6c18

bool TActionClass::unknown_chem_missile_at_waypoint(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Cell waypoint = unknown_id_source_a3d290->Get_Waypoint_Location(unknown_44);
    CoordStruct coord = CoordStruct(waypoint);
    coord.Z = Map.Unknown_0055A280(coord);
    if (Map[waypoint].unknown_140 & 0x100) {
        coord.Z += unknown_geometry_j;
    }
    Cell from = Map.Unknown_005689D0(Coord_Cell(coord), 0);
    WeaponTypeClass *launcher = unknown_WeaponTypeClass_list_00839b90[WeaponTypeClass::Index_From_Name("ChemLauncher")];
    BulletTypeClass *projectile = launcher->Projectile;
    BulletClass *bullet = Create_Bullet(projectile, (AbstractClass *)&Map[coord], 0, launcher->unknown_a4, launcher->Warhead, 20, false);
    if (bullet != 0) {
        double y = unknown_cos_4ba4d0(-9.587672516830327e-05);
        y *= unknown_sin_4ba480(1.5707483884323126);
        y *= 100.0;
        BulletVelocityXY planar(unknown_cos_4ba4d0(-9.587672516830327e-05) * unknown_cos_4ba4d0(1.5707483884323126) * 100.0, y);
        BulletVelocity velocity;
        velocity.XY() = planar;
        velocity.Z = unknown_sin_4ba480(-9.587672516830327e-05) * 100.0;
        bullet->unknown_slot118(CoordStruct(from.X * 256 + 128, from.Y * 256 + 128, 0), velocity);
        return true;
    }
    return false;
}


