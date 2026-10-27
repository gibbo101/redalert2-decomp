// int TechnoClass::unknown_6d7e20(int extra) (0x006D7E20)
// Fires the death weapon at the techno itself (hypothesis: the explosion
// when it dies): the type's DeathWeapon scaled by DeathWeaponDamageModifier,
// else the primary weapon scaled the same way, else the Rules DeathWeapon
// with half the type's MaxStrength. The damage plus extra goes to a new
// bullet that detonates at the centre; returns that damage, or 0 without a
// weapon.
#include "shared/techno.hpp"
#include "shared/rules.hpp"
#include "shared/weapon_type.hpp"
#include "shared/bullet.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Create_Bullet@@YIPAVBulletClass@@PAVBulletTypeClass@@PAVAbstractClass@@PAVTechnoClass@@HPAVWarheadTypeClass@@H_N@Z=00463990
// @ref ?Set_Weapon_Type@BulletClass@@QAEXPAVWeaponTypeClass@@@Z=00463ba0
// @ref ?unknown_func_462110@BulletClass@@QAEXABUCoordStruct@@@Z=00462110

int TechnoClass::unknown_6d7e20(int extra)
{
    WeaponTypeClass *weapon;
    int damage;
    if (unknown_slot32()->DeathWeapon != 0) {
        weapon = unknown_slot32()->DeathWeapon;
        damage = weapon->unknown_a4 * unknown_slot32()->DeathWeaponDamageModifier;
    } else {
        WeaponStruct *primary = unknown_slot230();
        if (primary != 0 && primary->WeaponType != 0) {
            weapon = unknown_slot230()->WeaponType;
            damage = weapon->unknown_a4 * unknown_slot32()->DeathWeaponDamageModifier;
        } else {
            weapon = Rules->DeathWeapon;
            damage = unknown_slot32()->MaxStrength * 0.5;
        }
    }
    if (weapon == 0) {
        return 0;
    }
    damage += extra;
    BulletClass *bullet = Create_Bullet(weapon->Projectile, this, this, damage, weapon->Warhead, 0, weapon->unknown_10b);
    if (bullet != 0) {
        bullet->Set_Weapon_Type(weapon);
        bullet->unknown_slot52();
        bullet->unknown_func_462110(Center_Coord());
        bullet->Release();
    }
    return damage;
}
