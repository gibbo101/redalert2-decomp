// @ref ??_C@_04JIKO@SQDG?$AA@=007eb7dc
// @ref __real@8@c0058000000000000000=007a7cf8
// Parasite grapple state machine, original 0x00606780 including its five-case dispatch.
#include "shared/foot.hpp"
#include "shared/cell.hpp"
#include "shared/techno_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/warhead_type.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"
#include "shared/id_source.hpp"
#include "shared/fast_math.hpp"
#include "shared/parasite.hpp"

void __fastcall Make_Wakes_00606E10(FootClass *victim, CoordStruct coord);

void ParasiteClass::Unknown_00606780()
{
    int damage;
    WeaponTypeClass *weapon = Owner->unknown_slot231(0)->WeaponType;
    WarheadTypeClass *warhead = weapon->Warhead;
    CoordStruct coord = unknown_28->Coord;
    CellClass *cell = (CellClass *)unknown_28->unknown_slot105();
    double sign = 1.0;
    if (!cell || cell->Is_Tile_Water()) {
        unknown_28->unknown_58c = CDTimerClass<FrameTimerClass>(warhead->Paralyzes);
        switch (unknown_48) {
        case 0: {
            unknown_28->unknown_280 = 0.0f;
            int index = AnimTypeClass::From_Name("SQDG");
            if (index != -1) {
                AnimTypeClass *type = AnimTypes[index];
                if (type) {
                    AnimClass *anim = new AnimClass(type, coord, 0, 1, 0x600, 0);
                    if (anim) {
                        Victim = (ParasiteVictim *)anim;
                        unknown_abstracts_ac0bf8.Add(this);
                    }
                }
            }
            unknown_48 = 1;
            Reset_Grapple_Counters_006066a0();
            Grapple_Frame_006066B0();
            break;
        }
        case 1:
            if (Grapple_Frame_006066B0()) {
                unknown_48 = unknown_id_source_a3d290->Random()(0, 1) ? 2 : 3;
                Reset_Grapple_Counters_006066a0();
                Grapple_Frame_006066B0();
                Make_Wakes_00606E10(unknown_28, coord);
            }
            break;
        case 2:
            sign = -1.0;
        case 3: {
            if (Grapple_Frame_006066B0()) {
                unknown_48 = 4;
                Reset_Grapple_Counters_006066a0();
                Grapple_Frame_006066B0();
            }
            double angle = unknown_4c * sign * 0.3141592653589793;
            unknown_28->unknown_280 = Fast_Sin(angle) * 0.78539819f;
            break;
        }
        case 4: {
            unknown_28->unknown_280 = 0.0f;
            int count = Rules->SplashList.Count();
            double angle = -unknown_28->unknown_2e0.Current().As_Radian();
            double cosine = Fast_Cos(angle);
            double sine = Fast_Sin(angle);
            for (int index = 0; index < 3; ++index) {
                double across = 64.0;
                double along = index * 128.0 - 128.0;
                if (unknown_id_source_a3d290->Random()(0, 1)) across = -64.0;
                int x = (int)(along * cosine - across * sine);
                int y = (int)(along * sine + across * cosine);
                CoordStruct splash = coord + CoordStruct(x, y, 0);
                new AnimClass(Rules->SplashList[unknown_id_source_a3d290->Random()(0, count - 1)], splash, 2, 1, 0x600, -10);
            }
            if (warhead->Culling && (unknown_28->unknown_func_5d46b0() == 0 ||
                (unknown_28->unknown_func_5d46b0() == 1 && Owner->unknown_118.unknown_713420()))) {
                if (Owner->unknown_slot32()->Trainable) {
                    TechnoTypeClass *victim_type = unknown_28->unknown_slot32();
                    TechnoTypeClass *owner_type = Owner->unknown_slot32();
                    Owner->unknown_118.Unknown_00713360(owner_type->unknown_slot33((int)Owner->House),
                        victim_type->unknown_slot33((int)unknown_28->House));
                }
                FootClass *victim = unknown_28;
                Unknown_00607440();
                victim->unknown_325 = true;
                victim->unknown_slot216((int)Owner);
                victim->unknown_slot210();
                Unknown_006064C0();
                Owner->unknown_58c = CDTimerClass<FrameTimerClass>(0);
                return;
            }
            damage = weapon->unknown_a4;
            unknown_28->unknown_slot86(&damage, 0, warhead, Owner, false, true);
            if (unknown_28) {
                unknown_48 = unknown_id_source_a3d290->Random()(0, 1) ? 2 : 3;
                Reset_Grapple_Counters_006066a0();
                Grapple_Frame_006066B0();
                Make_Wakes_00606E10(unknown_28, coord);
            } else {
                Unknown_006064C0();
            }
            break;
        }
        default:
            Unknown_00607440();
            break;
        }
        AnimClass *anim = (AnimClass *)Victim;
        if (anim && Owner && unknown_28) {
            CellClass *cell = (CellClass *)unknown_28->unknown_slot105();
            anim->Attach_To(unknown_28);
            anim->unknown_bc = Owner->unknown_slot115();
            if (cell) anim->unknown_e4 = cell->unknown_10a;
        }
    } else {
        Unknown_00607440();
        if (Owner) Owner->unknown_58c = CDTimerClass<FrameTimerClass>(0);
    }
}
