// Private Building mission139, full349+3; Rules+5E8 draft/compiler scope approved.
#include "shared/building.hpp"
#include "shared/rules.hpp"
// @ref ?unknown_443d60@BuildingClass@@QAEXH@Z=00443d60
// @ref ?Voc_Play_At@@YIPAUAudioEvent@@HABUCoordStruct@@PAUAudioEventHandle@@@Z=00713e60
// @ref ?Voc_Update_At@@YIPAUAudioEvent@@ABUCoordStruct@@PAUAudioEventHandle@@@Z=007141b0
// @ref ?Set_Current@FacingClass@@QAE_NABUUnknownFacingDir@@@Z=004b8b10
// @ref ?Free_Buildup@BuildingTypeClass@@QAEXXZ=0045e920
// @ref ?Unknown_00406070@UnknownAudioController@@QAEXXZ=00406070
int BuildingClass::unknown_slot139()
{
    switch(unknown_a8) {
    case 0:
        unknown_443d60(0);
        unknown_slot149(11);
        {
            int sound=Type->BuildupSound;
            if(sound==-1)sound=Rules->Construction;
            if(sound!=-1)Voc_Play_At(sound,CoordStruct(Coord),&unknown_570);
        }
        unknown_75=true;
        unknown_a8=1;
        break;
    case 1:
        unknown_75=true;
        Voc_Update_At(CoordStruct(Coord),&unknown_570);
        if(unknown_5ad) {
            unknown_slot149(12);
            unknown_slot149(3);
            unknown_443d60(1);
            unknown_slot282(false);
            unknown_slot116(5,false);
            if(!Type->LaserFence) {
                UnknownFacingDir direction((unsigned short)((unsigned char)Type->unknown_c64<<8));
                unknown_2e0.Set_Current(direction);
            }
            Type->Free_Buildup();
            unknown_570.Unknown_00406070();
            return 1;
        }
        break;
    }
    return 1;
}
