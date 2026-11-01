#include "shared/temporal.hpp"
#include "shared/unit.hpp"
#include "shared/spawn_manager.hpp"
#include "shared/capture_manager.hpp"
#include "shared/sidebar_building.hpp"
#include "shared/radar_event.hpp"
#include "shared/vox_class.hpp"
namespace seed_0044d320 { void __fastcall FUN_0044d320(int building); }

void TemporalClass::Unknown_006E27B0(TechnoClass *target)
{
    if(target!=0) {
        if(target->SpawnManager!=0) target->SpawnManager->Kill_Nodes();
        if(target->unknown_230!=0) ((CaptureManagerClass *)target->unknown_230)->Release_4681e0();
    }
    TemporalClass *owner_link=(TemporalClass *)Owner->unknown_208;
    if(owner_link!=0 && owner_link->Target!=0) owner_link->Let_Go_Of_Target();
    if(Can_Warp_Target(target) && Owner->unknown_20c==0) {
        Target=target;
        if(Target->unknown_20c==0) {
            target->unknown_20c=this;
            unknown_48=Target->unknown_slot32()->MaxStrength*10;
            if(Target!=0 && Target->Kind_Of()==1) {
                TechnoClass *object=Target;
                UnitClass *unit;
                if(object==0) unit=0;
                else unit=object->Kind_Of()==1 ? (UnitClass *)object:0;
                if(unit->Type->Harvester && Target->House==unknown_player_a35db4) {
                    Cell cell(Target->unknown_slot19(0));
                    if(Unknown_0063B5B0(4,cell)) Speech_Play_Name("EVA_OreMinerUnderAttack",-1,-1);
                }
            }
            if(Target->Kind_Of()==6 && !Target->unknown_slot32()->unknown_202 && !Target->unknown_slot31())
                Target->House->Attacked(As_Building(Target));
        } else {
            unknown_40=(TemporalClass *)Target->unknown_20c;
            unknown_44=unknown_40->unknown_44;
            unknown_40->unknown_44=this;
            if(unknown_44!=0) unknown_44->unknown_40=this;
        }
        Target->unknown_204=true;
        if(Target->Kind_Of()==6) {
            TechnoClass *building=Target;
            building->House->unknown_5668=true;
            seed_0044d320::FUN_0044d320((int)building);
            building->House->unknown_144=true;
        }
        Target->unknown_slot71(2);
        TemporalClass *target_link=(TemporalClass *)Target->unknown_208;
        if(target_link!=0 && target_link->Target!=0) target_link->Let_Go_Of_Target();
    }
}
// @ref ?FUN_0044d320@seed_0044d320@@YIXH@Z=0044d320
// @ref ??_C@_0BI@GJGA@EVA_OreMinerUnderAttack?$AA@=007f819c

// External references checked against complete original body operands.
// @ref ??_C@_0BI@GJGA@EVA_OreMinerUnderAttack?$AA@=007f819c
// @ref ?Attacked@HouseClass@@QAEXPAVTechnoClass@@@Z=004e4f60
// @ref ?FUN_0044d320@seed_0044d320@@YIXH@Z=0044d320
// @ref ?Kill_Nodes@SpawnManagerClass@@QAEXXZ=00689b70
// @ref ?Let_Go_Of_Target@TemporalClass@@QAEXXZ=006e2500
// @ref ?Release_4681e0@CaptureManagerClass@@QAEXXZ=004681e0
// @ref ?Speech_Play_Name@@YIXPBDHH@Z=00715b40
// @ref ?Unknown_0063B5B0@@YI_NHVCell@@@Z=0063b5b0
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
