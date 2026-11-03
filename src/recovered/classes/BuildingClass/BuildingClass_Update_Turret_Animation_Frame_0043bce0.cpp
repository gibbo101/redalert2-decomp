// BuildingClass Set_Turret_Frame 0x0043BCE0 (TibSun building.cpp Set_Turret_Frame without the charge animation).
// Free fastcall versus nonvirtual-member spelling remains a source hypothesis.
#include "shared/building.hpp"
#include "shared/anim.hpp"
extern "C" int const unknown_turret_frame_table_007acab0[32];
// @ref _unknown_turret_frame_table_007acab0=007acab0
int __fastcall Building_Update_Turret_Animation_Frame_0043bce0(BuildingClass *building)
{
    int stage = 0;
    int reset_step = false;

    if (building->unknown_slot232()) {
        if (building->unknown_454[9] != 0) {
            stage = unknown_turret_frame_table_007acab0[Dir_To_32(building->unknown_2e0.Current())];
            reset_step = true;

            AnimClass *anim = static_cast<AnimClass *>(building->unknown_454[9]);
            if (anim != 0) {
                anim->Set_Stage(stage);
                if (reset_step) {
                    anim->Set_Step(0);
                }
            }
        }
    }
    return(stage);
}
