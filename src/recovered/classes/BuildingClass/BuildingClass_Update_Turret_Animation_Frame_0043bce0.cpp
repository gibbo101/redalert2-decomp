// Building-family animation-frame update at 0x0043BCE0.
// Free fastcall versus nonvirtual-member spelling remains a source hypothesis.
#include "shared/building.hpp"
#include "shared/anim.hpp"
extern "C" int const unknown_turret_frame_table_007acab0[32];
// @ref _unknown_turret_frame_table_007acab0=007acab0
inline int Building_Set_Animation_Frame_0043bce0(AnimClass *anim, int frame)
{
    if (anim) {
        int &stage=anim->Stage;
        int &step=anim->Step;
        stage=frame;
        step=0;
        return frame;
    }
    return frame;
}
int __fastcall Building_Update_Turret_Animation_Frame_0043bce0(BuildingClass *building)
{
    int result=0;
    if (building->unknown_slot232() && building->unknown_454[9]) {
        UnknownFacingDir direction=building->unknown_2e0.Current();
        AnimClass *anim=static_cast<AnimClass *>(building->unknown_454[9]);
        int frame=unknown_turret_frame_table_007acab0[Dir_To_32(direction)];
        result=Building_Set_Animation_Frame_0043bce0(anim,frame);
    }
    return result;
}
