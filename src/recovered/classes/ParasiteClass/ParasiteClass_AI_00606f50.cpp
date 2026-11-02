#include "shared/foot.hpp"
#include "shared/techno_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/warhead_type.hpp"
#include "shared/rules.hpp"
#include "shared/anim.hpp"
#include "shared/particle_system.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/parasite.hpp"
// @ref _unknown_geometry_l=00a76468
// @ref ?unknown_facing_radians_79b620@@3NB=0079b620
// @ref ?unknown_sin_4ba480@@YANN@Z=004ba480
// @ref ?unknown_cos_4ba4d0@@YANN@Z=004ba4d0
// @ref ?Unknown_00606780@ParasiteClass@@QAEXXZ=00606780

extern double const unknown_facing_radians_79b620;
double __cdecl unknown_sin_4ba480(double angle);
double __cdecl unknown_cos_4ba4d0(double angle);

void ParasiteClass::AI()
{
    if (unknown_28 == 0) {
        return;
    }
    if (unknown_28->unknown_slot32()->Naval && !unknown_28->unknown_slot32()->Organic
        && Owner->unknown_slot32()->Naval && Owner->unknown_slot32()->Organic) {
        Unknown_00606780();
        return;
    }
    WeaponTypeClass *weapon = Owner->unknown_slot231(0)->WeaponType;
    WarheadTypeClass *warhead = weapon->Warhead;
    CoordStruct coord = unknown_28->Coord;
    if (unknown_38.Value() != 0) {
        return;
    }
    unknown_38 = CDTimerClass<FrameTimerClass>(weapon->unknown_b0);
    unknown_28->unknown_58c = CDTimerClass<FrameTimerClass>(warhead->Paralyzes);
    int damage;
    if (unknown_28->Kind_Of() == 15) {
        damage = unknown_28->Strength;
        unknown_28->unknown_slot86(&damage, 0, warhead, Owner, true, true);
    } else {
        new ParticleSystemClass(Rules->unknown_ce0, coord, 0, 0, unknown_geometry_l);
        UnknownFacingDir dir = unknown_28->unknown_2e0.Current();
        if (weapon->Anim.Count() != 0) {
            AnimTypeClass *anim = weapon->Anim[Dir_To_8(dir)];
            if (anim != 0) {
                new AnimClass(anim, coord, 0, 1, 0x600, 0);
            }
        }
        UnknownFacingDir perpendicular = dir.Left_90();
        int distance = unknown_id_source_a3d290->Random()(0, 1) ? -2 : 2;
        double angle = perpendicular.As_Radian();
        int z = coord.Z;
        int y = (int)(coord.Y - unknown_sin_4ba480(angle) * distance);
        int x = (int)(unknown_cos_4ba4d0(angle) * distance + coord.X);
        CoordStruct push(x, y, z);
        unknown_28->unknown_slot223(push, 1.5f);
        damage = weapon->unknown_a4;
        unknown_28->unknown_slot86(&damage, 0, warhead, Owner, false, true);
    }
}
