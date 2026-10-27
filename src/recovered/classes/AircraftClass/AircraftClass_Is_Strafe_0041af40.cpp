// long __stdcall AircraftClass::Is_Strafe() (0x0041AF40, IFlyControl slot 6)
// Whether the primary weapon's projectile is visible and turns at most 1.
#include "shared/aircraft.hpp"

long __stdcall AircraftClass::Is_Strafe()
{
    WeaponStruct *weapon = unknown_slot231(0);
    if (weapon == 0) {
        return 0;
    }
    WeaponTypeClass *weapon_type = weapon->WeaponType;
    if (weapon_type == 0) {
        return 0;
    }
    BulletTypeClass *projectile = weapon_type->Projectile;
    if (projectile->ROT > 1) {
        return 0;
    }
    return !projectile->Inviso;
}
