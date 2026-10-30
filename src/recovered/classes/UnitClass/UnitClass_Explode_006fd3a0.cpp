// UnitClass death animations and stored-resource explosion strength.
#include "shared/unit.hpp"
#include "shared/anim.hpp"
#include "shared/rules.hpp"
#include "shared/id_source.hpp"
#include "shared/tiberium.hpp"

// The original passes a shake magnitude in ECX to this disabled engine hook.
void __fastcall Unit_Unknown_Shake_00482e00(int magnitude);
// @ref ?Unit_Unknown_Shake_00482e00@@=00482e00
// @ref ?Get_Total_Amount@StorageClass@@=0069ae10
// @ref ?Get_Amount@StorageClass@@=0069ae40

void UnitClass::unknown_6fd3a0()
{
    if (Type->Explosion.Count()>0) {
        AnimTypeClass *animation=Type->Explosion.Pick(unknown_id_source_a3d290->Random());
        if ((Type->Explodes || unknown_6d7910(10)) && (Type->Ammo==-1 || unknown_254>0)) {
            animation=Type->Explosion[Type->Explosion.Count()-1];
        }
        new AnimClass(animation,Position_Coord_004f3f40(),0,1,0x600,0);
        if (unknown_294.Get_Total_Amount()>0 && Rules->unknown_1429 && !(unknown_id_source_a3d290->unknown_000&0x800)) {
            int power=0;
            for (int i=0;i<unknown_TiberiumClass_list_00ac0b30.Count();i++) {
                power+=unknown_294.Get_Amount(i)*unknown_TiberiumClass_list_00ac0b30[i]->Power;
            }
        }
        if (Type->MaxStrength>Rules->unknown_4e8) {
            int shakes=Type->MaxStrength/(Rules->unknown_4e8/2)+3;
            Unit_Unknown_Shake_00482e00(shakes<6?shakes:6);
        }
    }
    if (Type->DestroyAnim.Count()>0) {
        AnimTypeClass *animation=Type->DestroyAnim.Pick(unknown_id_source_a3d290->Random());
        new AnimClass(animation,Position_Coord_004f3f40(),0,1,0x600,0);
    }
}
