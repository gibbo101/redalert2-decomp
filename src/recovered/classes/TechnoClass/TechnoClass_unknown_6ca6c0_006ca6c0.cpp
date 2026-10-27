// int TechnoClass::unknown_6ca6c0(TechnoClass *target, WeaponTypeClass *weapon) (0x006CA6C0)
// The damage a weapon would do to target (0 without a target or for a
// weapon flagged +0x10C or +0x105): Damage times the owner's +0xD0 and the
// techno's +0x128 multipliers (and VeteranCombat for a veteran/elite with
// ability 2), divided by the target owner's armor multiplier against this
// type times +0x120 (and VeteranArmor for a target with ability 1), at
// least 1, then through the warhead against the target's armor
// (0x0047E1C0).
#include "shared/techno.hpp"
#include "shared/rules.hpp"
#include "shared/weapon_type.hpp"
#include "shared/warhead_type.hpp"
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_func_4f58a0@HouseClass@@QAEMPAVTechnoTypeClass@@@Z=004f58a0
// @ref ?Unknown_0047E1C0@@YIHHPAVWarheadTypeClass@@HH@Z=0047e1c0

int TechnoClass::unknown_6ca6c0(TechnoClass *target, WeaponTypeClass *weapon)
{
    if (target == 0) {
        return 0;
    }
    int damage = weapon->unknown_a4;
    if (weapon->unknown_10c || weapon->unknown_105) {
        return 0;
    }
    if (damage > 0) {
        damage = House->unknown_d0 * unknown_128 * damage;
        if (unknown_118.unknown_7133a0() || unknown_118.unknown_713420()) {
            TechnoTypeClass *type = unknown_slot32();
            if ((unknown_118.unknown_7133a0() && type->VeteranAbilities.Ability[2])
                || (unknown_118.unknown_713420() && (type->VeteranAbilities.Ability[2] || type->EliteAbilities.Ability[2]))) {
                damage = damage * Rules->VeteranCombat;
            }
        }
        double value = damage;
        damage = value / (target->House->unknown_func_4f58a0(unknown_slot32()) * unknown_120);
        if (target->unknown_118.unknown_7133a0() || target->unknown_118.unknown_713420()) {
            TechnoTypeClass *type = target->unknown_slot32();
            if ((target->unknown_118.unknown_7133a0() && type->VeteranAbilities.Ability[1])
                || (target->unknown_118.unknown_713420() && (type->VeteranAbilities.Ability[1] || type->EliteAbilities.Ability[1]))) {
                damage = damage / Rules->VeteranArmor;
            }
        }
        if (damage < 1) {
            damage = 1;
        }
        damage = Unknown_0047E1C0(damage, weapon->Warhead, target->Class_Of()->unknown_9c, 0);
    }
    return damage;
}
