// Original: 748 body bytes including 28 switch-table bytes; four frozen NOPs.
// Clear a detached building animation and restart the appropriate follow-up state.
#include "shared/building.hpp"
#include "shared/anim.hpp"
// @ref ?In_Radio_Contact@RadioClass@@=00636f10
// @ref ?unknown_44ca60@BuildingClass@@=0044ca60
// @ref ?Health_Ratio@ObjectClass@@=005d4540
void BuildingClass::unknown_44cce0(AbstractClass *object)
{
    if(!unknown_7d) return;
    for(int index=0;index<18;++index) {
        if(unknown_454[index]!=object) continue;
        unknown_454[index]=0;
        AnimClass *animation=static_cast<AnimClass *>(object);
        switch(index) {
        case 10:
            if(Type->UnitRepair) {
                if(In_Radio_Contact() && unknown_slot91()==20) {
                    unknown_44c920(11,Health_Ratio()<=Rules->unknown_1368,false,0);
                    return;
                }
                unknown_44c920(17,Health_Ratio()<=Rules->unknown_1368,false,0);
            } else if(Type->IsAnimDelayedFire && animation->unknown_159) {
                unknown_44c920(3,Health_Ratio()<=Rules->unknown_1368,unknown_554.Count()>0,0);
            }
            break;
        case 12:
            if(Type->UnitRepair && animation->unknown_159)
                unknown_44c920(17,Health_Ratio()<=Rules->unknown_1368,false,0);
            break;
        case 14:
            if(animation->unknown_159)
                unknown_44c920(15,Health_Ratio()<=Rules->unknown_1368,false,0);
            break;
        case 16:
            if(animation->unknown_159)
                unknown_44c920(13,Health_Ratio()<=Rules->unknown_1368,false,0);
            break;
        }
        return;
    }
}
