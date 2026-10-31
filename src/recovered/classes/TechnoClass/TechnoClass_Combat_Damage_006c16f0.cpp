// Weapon damage and ambient damage, averaged for an unspecified weapon.
// Existing nonconst member ABI retained; operation name remains a hypothesis.
#include "shared/techno.hpp"
#include "shared/weapon_type.hpp"
int TechnoClass::unknown_6c16f0(int weapon)
{
    int value=0;
    if(weapon==-1) {
        int divisor=0;
        if(unknown_slot32()->Has_Turret_Weapons()) {
            WeaponStruct *slot=unknown_slot231(unknown_10c);
            if(!slot) return 0;
            if(!slot->WeaponType) return 0;
            value+=slot->WeaponType->unknown_a4;
            value+=slot->WeaponType->unknown_98;
            divisor=1;
        } else {
            if(unknown_slot231(0)->WeaponType) {
                value+=unknown_slot231(0)->WeaponType->unknown_a4;
                value+=unknown_slot231(0)->WeaponType->unknown_98;
                divisor=1;
            }
            if(unknown_slot231(1)->WeaponType) {
                value+=unknown_slot231(1)->WeaponType->unknown_a4;
                value+=unknown_slot231(1)->WeaponType->unknown_98;
                ++divisor;
            }
        }
        if(divisor>0) return value/divisor;
        return 0;
    } else {
        if(unknown_slot231(weapon)->WeaponType) {
            value+=unknown_slot231(weapon)->WeaponType->unknown_a4;
            value+=unknown_slot231(weapon)->WeaponType->unknown_98;
        }
        return value;
    }
}
