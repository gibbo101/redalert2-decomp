// ObjectClass damage handler005D3D20; original1079+9.
// Private strict candidate; source and field types remain explicit hypotheses.
// Existing six-argument ABI and field meanings remain explicit hypotheses.
#include "shared/object_type.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/infantry.hpp"
#include "shared/infantry_type.hpp"
#include "shared/anim.hpp"
#include "shared/tag.hpp"
#include "shared/rules.hpp"
int __fastcall Unknown_0047E1C0(int damage, WarheadTypeClass *warhead, int armour, int distance);
extern double const unknown_cyborg_recovery_007a7670;
// @ref ?Unknown_0047E1C0@@=0047e1c0
// @ref ?unknown_cyborg_recovery_007a7670@@3NB=007a7670
// @ref ??0AnimClass@@=00420110
// @ref ?Unknown_006B3DF0@TagClass@@=006b3df0
// @ref _unknown_geometry_k=00a72ee0
int ObjectClass::unknown_slot86(int *damage, int distance, WarheadTypeClass *warhead,
    TechnoClass *source, bool forced, int unknown_argument)
{
    int state = 0;
    {
    int old_strength = Strength;
    if (old_strength <= 0 || *damage == 0 || (!forced && Class_Of()->unknown_203)) goto damage_done;
    int maximum_strength = Class_Of()->MaxStrength;
    if (!forced) *damage = Unknown_0047E1C0(*damage, warhead, Class_Of()->unknown_9c, distance);
    if (*damage == 0) return 0;
    if (*damage < 0) {
        int before_heal = Strength;
        Strength = (int)((unsigned int)before_heal - (unsigned int)*damage);
        if (Strength > maximum_strength) Strength = maximum_strength;
        if (before_heal != Strength) unknown_slot79(7);
        return 0;
    }
    state = 1;
    if (old_strength > *damage) {
        if (old_strength >= (maximum_strength >> 1) &&
            (int)((unsigned int)old_strength - (unsigned int)*damage) < (maximum_strength >> 1)) state = 2;
    } else *damage = old_strength;
    double threshold = (double)maximum_strength * Rules->unknown_1370;
    if ((double)old_strength > threshold &&
        (double)(int)((unsigned int)old_strength - (unsigned int)*damage) < threshold) state = 3;
    Strength = (int)((unsigned int)old_strength - (unsigned int)*damage);
    if (Strength <= 0 && Kind_Of() == 15 && !forced) {
        InfantryClass *infantry = static_cast<InfantryClass *>(this);
        if (infantry->Type->Cyborg && !infantry->unknown_5c3) {
            new AnimClass(Rules->InfantryExplode, CoordStruct(Coord), 0, 1, 0x600, 0);
            Strength = (int)((double)infantry->Type->MaxStrength * unknown_cyborg_recovery_007a7670);
            int restored_strength = Strength;
            if (restored_strength <= 1) restored_strength = 1;
            Strength = restored_strength;
            infantry->unknown_5c3 = true;
            infantry->unknown_slot311(6, true, false);
            state = 3;
        }
    }
    int strength_after_damage = Strength;
    if (state == 2) {
        if (source && unknown_34) unknown_34->Spring(39, this, unknown_geometry_k, 0, 0);
        if (!unknown_7d) goto damage_interrupted;
        if (unknown_34) unknown_34->Spring(42, this, unknown_geometry_k, 0, 0);
    }
    if (unknown_7d) {
        if (state == 3) {
            if (source && unknown_34) unknown_34->Spring(40, this, unknown_geometry_k, 0, 0);
            if (!unknown_7d) goto damage_interrupted;
            if (unknown_34) unknown_34->Spring(43, this, unknown_geometry_k, 0, 0);
        }
        if (unknown_7d) {
            if (Strength != old_strength && Class_Of() && old_strength == Class_Of()->MaxStrength) {
                if (source && unknown_34) unknown_34->Spring(38, this, unknown_geometry_k, 0, 0);
                if (unknown_34 && unknown_7d) unknown_34->Spring(41, this, unknown_geometry_k, 0, 0);
                if (unknown_34) {
                    if (!unknown_7d) goto damage_interrupted;
                    if (source) unknown_34->Spring(41, this, unknown_geometry_k, 0, reinterpret_cast<int>(source));
                }
            }
            if (unknown_7d && (strength_after_damage <= 0 || Strength > 0)) {
                if (Strength == 0) {
                    unknown_slot55(source);
                    state = 4;
                    unknown_slot54(true);
                }
                if (!unknown_7d) goto damage_done;
                if (source && unknown_34 && state != 4)
                    unknown_34->Spring(6, this, unknown_geometry_k, 0, reinterpret_cast<int>(source));
                if (!unknown_7d) goto damage_done;
                if (source && unknown_34 && state != 4)
                    unknown_34->Spring(44, this, unknown_geometry_k, 0, reinterpret_cast<int>(source));
                if (!unknown_7d) goto damage_done;
                if (state == 0) goto damage_done;
                if (!unknown_77) goto damage_done;
                unknown_slot71(2);
                goto damage_done;
            }
        }
    }
    goto damage_interrupted;
    }
damage_done:
    return state;
damage_interrupted:
    return 5;
}
