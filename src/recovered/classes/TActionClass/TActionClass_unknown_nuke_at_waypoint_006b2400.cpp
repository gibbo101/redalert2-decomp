// bool TActionClass::unknown_nuke_at_waypoint(...) (0x006B2400)
// A NukePayload bullet (speed 50) aimed at the cell of waypoint +0x44 (ground height, raised on a bridge), given the weapon, placed 20000 leptons above it and launched straight down at speed 100 (the pitch of 0x00463C50); false when the bullet cannot be created. Like 0x00463C50 the weapon is set before the null test.
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
// @ref ??_C@_0M@BCEA@NukePayload?$AA@=007d1240
// @ref _unknown_geometry_j=00abfdf8
// @ref __real@8@c005c800000000000000=007a5fc8

bool TActionClass::unknown_nuke_at_waypoint(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    Cell waypoint = unknown_id_source_a3d290->Get_Waypoint_Location(unknown_44);
    CoordStruct coord = Cell_Center(waypoint);
    coord.Z = Map.Unknown_0055A280(coord);
    if (Map[waypoint].unknown_140 & 0x100) {
        coord.Z += unknown_geometry_j;
    }
    WeaponTypeClass *payload = unknown_WeaponTypeClass_list_00839b90[WeaponTypeClass::Index_From_Name("NukePayload")];
    BulletTypeClass *projectile = payload->Projectile;
    BulletClass *bullet = Create_Bullet(projectile, (AbstractClass *)&Map[coord], 0, payload->unknown_a4, payload->Warhead, 50, false);
    bullet->Set_Weapon_Type(payload);
    CoordStruct launch = coord + CoordStruct(0, 0, 20000);
    if (bullet != 0) {
        double y = unknown_sin_4ba480(1.5707483884323126);
        y *= unknown_cos_4ba4d0(1.5707483884323126);
        y *= -100.0;
        BulletVelocityXY planar(unknown_cos_4ba4d0(1.5707483884323126) * unknown_cos_4ba4d0(1.5707483884323126) * -100.0, y);
        BulletVelocity velocity;
        velocity.XY() = planar;
        velocity.Z = unknown_sin_4ba480(1.5707483884323126) * -100.0;
        bullet->unknown_slot118(launch, velocity);
        return true;
    }
    return false;
}
