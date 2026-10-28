// AnimTypeClass *__fastcall Select_Damage_Anim(int damage, WarheadTypeClass *warhead, int land, CoordStruct *coords) -- 0x0047F4D0
// Purpose: picks the animation a warhead leaves where it hits. Conventional
// warheads over water (land 2) low enough in the cell use the splash list; the
// lightning warhead its own animation; otherwise the warhead's list, the
// stronger the damage the later the entry (one entry per 25 points; the
// EMP-style warheads draw one at random).
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/map_view.hpp"
#include "shared/map_cell.hpp"
#include "shared/rules.hpp"
#include "shared/warhead_type.hpp"
#include "shared/anim_type.hpp"
#include "shared/abstract.hpp"
#include "shared/unknown_geometry.hpp"
#include "shared/type_list.hpp"

AnimTypeClass *__fastcall Select_Damage_Anim(int damage, WarheadTypeClass *warhead, int land, CoordStruct *coords)
{
    if (damage != 0 && warhead != 0) {
        if (land == 2 && warhead->Conventional && !(Map[*coords].unknown_140 & 0x100)
            && coords->Z < Map.Unknown_0055A280(*coords) + unknown_geometry_g * 2) {
            if (Rules->SplashList.Count() == 0) {
                return 0;
            }
            int last = Rules->SplashList.Count() * 35 - 1;
            if (damage < last) {
                last = damage;
            }
            return Rules->SplashList[last / 35];
        }
        if (warhead == Rules->LightningWarhead) {
            return Rules->WeatherConBoltExplosion;
        }
        int count = warhead->AnimList.Count();
        if (count != 0) {
            if (warhead->EMEffect) {
                return warhead->AnimList[unknown_id_source_a3d290->Random()(0, count - 1)];
            }
            count = count * 25 - 1;
            if (damage >= count) {
                damage = count;
            }
            return warhead->AnimList[damage / 25];
        }
    }
    return 0;
}
