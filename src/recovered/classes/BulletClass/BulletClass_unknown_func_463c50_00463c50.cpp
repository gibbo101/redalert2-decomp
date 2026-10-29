// void BulletClass::unknown_func_463c50() (0x00463C50)
// A NukeMaker warhead's payload (hypothesis): a bullet of the weapon named
// NukePayload, bright, aimed at the target and owned by this bullet's owner,
// is placed above the centre of the target's cell (this bullet's weapon's
// projectile DetonationAltitude higher) and launched straight down (the
// direction and pitch 0x3FFF steps, speed -1).
#include "shared/bullet.hpp"
#include "shared/bullet_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/cell.hpp"
#include "shared/map_view.hpp"
// @ref ?Index_From_Name@WeaponTypeClass@@SIHPBD@Z=00733f30
// @ref ??_C@_0M@BCEA@NukePayload?$AA@=007d1240

void BulletClass::unknown_func_463c50()
{
    AbstractClass *target = Target;
    CellClass *target_cell = &Map[Coord_Cell_Of(target->Center_Coord())];
    WeaponTypeClass *payload = unknown_WeaponTypeClass_list_00839b90[WeaponTypeClass::Index_From_Name("NukePayload")];
    BulletTypeClass *projectile = payload->Projectile;
    WarheadTypeClass *warhead = payload->Warhead;
    int speed = payload->unknown_a8;
    int damage = payload->unknown_a4;
    TechnoClass *owner = Owner;
    BulletClass *bullet = Create_Bullet(projectile, target, owner, damage, warhead, speed, true);
    if (bullet != 0) {
        bullet->unknown_slot52();
        bullet->Set_Weapon_Type(payload);
        CoordStruct launch = target_cell->Center_Coord();
        launch = launch + CoordStruct(0, 0, WeaponType->Projectile->DetonationAltitude);
        double y = unknown_sin_4ba480(1.5707483884323126);
        y *= unknown_cos_4ba4d0(1.5707483884323126);
        y *= -1.0;
        BulletVelocityXY planar(unknown_cos_4ba4d0(1.5707483884323126) * unknown_cos_4ba4d0(1.5707483884323126) * -1.0, y);
        BulletVelocity velocity;
        velocity.XY() = planar;
        velocity.Z = unknown_sin_4ba480(1.5707483884323126) * -1.0;
        bullet->unknown_slot118(launch, velocity);
    }
}
