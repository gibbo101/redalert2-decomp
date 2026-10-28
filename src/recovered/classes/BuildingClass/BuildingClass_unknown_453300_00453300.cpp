// Private Building ownership/garrison update, complete original331+5.
// Passes the new owner house to TechnoClass slot 222, which is still declared (int, int); its HouseClass * signature is a pending rename batch.
#include "shared/building.hpp"
#include "shared/house.hpp"
#include "shared/side.hpp"
#include "shared/infantry.hpp"
#include "shared/rules.hpp"
extern "C" char const unknown_side_civilian_007ceb30[];
extern "C" char const unknown_eva_structure_abandoned_007cfc14[];
extern "C" char const unknown_eva_structure_garrisoned_007cfbfc[];
// @ref _unknown_side_civilian_007ceb30=007ceb30
// @ref _unknown_eva_structure_abandoned_007cfc14=007cfc14
// @ref _unknown_eva_structure_garrisoned_007cfbfc=007cfbfc
// @ref ?unknown_452f50@BuildingClass@@QAEXH@Z=00452f50
// @ref ?Find_Index@SideClass@@SIHPBD@Z=0067af90
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Voc_Play@@YIPAUAudioEvent@@HMHPAUAudioEventHandle@@@Z=00713db0
// @ref ?Unknown_0063B5B0@@YI_NHVCell@@@Z=0063b5b0
// @ref ?Unknown_00715B40@@YIHPBDHH@Z=00715b40
// @ref ?Voc_Play_At@@YIPAUAudioEvent@@HABUCoordStruct@@PAUAudioEventHandle@@@Z=00713e60
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
void BuildingClass::unknown_453300()
{
    if((char)unknown_func_5d45b0())unknown_452f50(0);
    int count=Houses.Count();
    HouseClass *civilian=0;
    int side=SideClass::Find_Index(unknown_side_civilian_007ceb30);
    if(count>0) {
        HouseClass **cursor=&Houses[0];
        do {
            HouseClass *house=*cursor;
            if(house->Type->Side==side)civilian=house;
            ++cursor;
        }while(--count);
    }
    if(unknown_554.Count()==0) {
        if(House!=civilian) {
            if(House->Unknown_004F52B0()) {
                Voc_Play(Rules->BuildingAbandonedSound,1.0f,0x2000,0);
                if(Unknown_0063B5B0(15,unknown_slot104()))
                    Unknown_00715B40(unknown_eva_structure_abandoned_007cfc14,-1,-1);
            }
            Refresh_State_Animations_00453450();
            unknown_slot222(civilian,0);
        }
    }
    if(unknown_554.Count()>0 && House==civilian) {
        Refresh_State_Animations_00453450();
        unknown_slot222(unknown_554[0]->House,0);
        if(unknown_554[0]->House->Unknown_004F52B0()) {
            Unknown_00715B40(unknown_eva_structure_garrisoned_007cfbfc,-1,-1);
            Voc_Play_At(Rules->BuildingGarrisonedSound,Center_Coord(),0);
        }
    }
}
