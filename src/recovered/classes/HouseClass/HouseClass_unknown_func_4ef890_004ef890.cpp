// @ref ??_7?$VectorClass@PBVBuildingTypeClass@@@@6B@=007a2f08
// @ref ??_E?$VectorClass@PBVBuildingTypeClass@@@@UAEPAXI@Z=004f8490
// @ref ??_G?$VectorClass@PBVBuildingTypeClass@@@@UAEPAXI@Z=004f8490
// @ref ??8?$VectorClass@PBVBuildingTypeClass@@@@UBE_NABV0@@Z=004f7010
// @ref ?Resize@?$VectorClass@PBVBuildingTypeClass@@@@UAE_NHPBQBVBuildingTypeClass@@@Z=004f7050
// @ref ?Clear@?$VectorClass@PBVBuildingTypeClass@@@@UAEXXZ=004f7100
// @ref ?ID@?$VectorClass@PBVBuildingTypeClass@@@@UAEHABQBVBuildingTypeClass@@@Z=004f7130
// @ref ?ID@?$VectorClass@PBVBuildingTypeClass@@@@UAEHPBQBVBuildingTypeClass@@@Z=004f7170
// @ref ?Fetch@?$VectorClass@PBVBuildingTypeClass@@@@UBEPBVBuildingTypeClass@@H@Z=004f6c50
// @ref ??_7?$DynamicVectorClass@PBVBuildingTypeClass@@@@6B@=007a2f28
// @ref ??_E?$DynamicVectorClass@PBVBuildingTypeClass@@@@UAEPAXI@Z=004f84e0
// @ref ??_G?$DynamicVectorClass@PBVBuildingTypeClass@@@@UAEPAXI@Z=004f84e0
// @ref ?Resize@?$DynamicVectorClass@PBVBuildingTypeClass@@@@UAE_NHPBQBVBuildingTypeClass@@@Z=004f7190
// @ref ?Clear@?$DynamicVectorClass@PBVBuildingTypeClass@@@@UAEXXZ=004f6c00
// @ref ?ID@?$DynamicVectorClass@PBVBuildingTypeClass@@@@UAEHABQBVBuildingTypeClass@@@Z=004f7240
// @ref ?ID@?$DynamicVectorClass@PBVBuildingTypeClass@@@@UAEHPBQBVBuildingTypeClass@@@Z=004f6c30
// @ref ??_7?$VectorClass@_N@@6B@=007a2f64
// @ref ??_E?$VectorClass@_N@@UAEPAXI@Z=004f8760
// @ref ??_G?$VectorClass@_N@@UAEPAXI@Z=004f8760
// @ref ??8?$VectorClass@_N@@UBE_NABV0@@Z=004f7e40
// @ref ?Resize@?$VectorClass@_N@@UAE_NHPB_N@Z=004f7e80
// @ref ?Clear@?$VectorClass@_N@@UAEXXZ=004f7f30
// @ref ?ID@?$VectorClass@_N@@UAEHAB_N@Z=004f7f60
// @ref ?ID@?$VectorClass@_N@@UAEHPB_N@Z=004f7fa0
// @ref ?Fetch@?$VectorClass@_N@@UBE_NH@Z=004f6e50
// @ref ??_7?$DynamicVectorClass@_N@@6B@=007a2f84
// @ref ??_E?$DynamicVectorClass@_N@@UAEPAXI@Z=004f87b0
// @ref ??_G?$DynamicVectorClass@_N@@UAEPAXI@Z=004f87b0
// @ref ?Resize@?$DynamicVectorClass@_N@@UAE_NHPB_N@Z=004f7fc0
// @ref ?Clear@?$DynamicVectorClass@_N@@UAEXXZ=004f6e00
// @ref ?ID@?$DynamicVectorClass@_N@@UAEHAB_N@Z=004f8070
// @ref ?ID@?$DynamicVectorClass@_N@@UAEHPB_N@Z=004f6e30
// @ref ??0?$VectorClass@_N@@QAE@IPB_N@Z=004f8d20
// @ref ??_C@_06JNA@GAPLUG?$AA@=007da918
// House base-plan construction, original004EF890;2545 body+15 NOP.
// Negative queue pointers represent the original special base-node kinds.
// @ref ??_7?$DynamicVectorClass@PBVBuildingTypeClass@@@@6B@=007a2f28
// @ref ??_7?$DynamicVectorClass@_N@@6B@=007a2f84
// @ref ??_7?$VectorClass@_N@@6B@=007a2f64
#include "shared/building_class.hpp"
#include "shared/building_type_class.hpp"
#include "shared/building_type_list.hpp"
#include "shared/super.hpp"
#include "shared/rules.hpp"
#include "shared/crt_string.hpp"
void HouseClass::unknown_func_4ef890()
{
    bool soviet=unknown_130==1;
    unknown_55f0.Init();
    int owner=1 << HouseTypeClass::Find_Index(Type->ParentCountry);
    DynamicVectorClass<BuildingTypeClass const *> eligible;
    DynamicVectorClass<bool> included;
    int i;
    for (i=0;i<BuildingTypes.Count();++i) {
        BuildingTypeClass const *type=BuildingTypes[i];
        if ((type->Owner & owner) && (type->AIBasePlanningSide==Type->Side || type->AIBasePlanningSide==-1)
            && type->AIBuildThis && type->TechLevel<=unknown_11c
            && (type->RequiredHouses==-1 || (type->RequiredHouses & (1 << Type->House)))
            && (type->ForbiddenHouses==-1 || !(type->ForbiddenHouses & (1 << Type->House)))
            && (unknown_session_a3d2c3 || type->SuperWeapon==-1 || !Supers[type->SuperWeapon]->Type->DisableableFromShell)) {
            eligible.Add(type);
            included.Add(false);
        }
    }
    int eligible_count=eligible.Count();
    DynamicVectorClass<BuildingTypeClass const *> ordered;
    BuildingTypeClass const *yard=unknown_func_4ef600(Rules->unknown_7c8);
    for (i=0;i<eligible_count;++i) {
        if (yard==eligible[i]) { included[i]=true; ordered.Add(yard); break; }
    }
    ordered.Add(unknown_func_4ef600(Rules->BuildPower));
    BuildingTypeClass const *barracks=unknown_func_4ef600(Rules->BuildBarracks);
    for (i=0;i<eligible.Count();++i) {
        if (eligible[i]==barracks) {
            BuildingTypeClass const *first=eligible[0]; eligible[0]=barracks;
            included[i]=included[0]; included[0]=false; eligible[i]=first; break;
        }
    }
    BuildingTypeClass const *weapons=unknown_func_4ef600(Rules->BuildWeapons);
    for (i=0;i<eligible.Count();++i) {
        if (eligible[i]==weapons) {
            BuildingTypeClass const *second=eligible[1]; eligible[1]=weapons;
            included[i]=included[1]; included[1]=false; eligible[i]=second; break;
        }
    }
    int remaining=eligible_count-1;
    while (remaining>0) {
        int plug=-1;
        bool added=false;
        int queued=ordered.Count();
        for (i=0;i<eligible_count;++i) {
            if (included[i]) continue;
            BuildingTypeClass const *type=eligible[i];
            if (_stricmp(type->ID,"GAPLUG")==0) { plug=i; continue; }
            if (unknown_func_4ef740((BuildingTypeClass *)type,ordered,queued)) {
                included[i]=true; ordered.Add(type); added=true; --remaining;
            }
        }
        if (!added) {
            if (plug==-1) break;
            included[plug]=true; ordered.Add(eligible[plug]); --remaining;
        }
    }
    int extra_refineries=2-unknown_c8;
    BuildingTypeClass const *refinery=unknown_func_4ef600(Rules->BuildRefinery);
    int refinery_position=0;
    for (i=0;i<ordered.Count()-1;++i) {
        if (ordered[i]==refinery) {
            if (refinery_position!=-1 && extra_refineries>0) {
                for (int n=0;n<extra_refineries;++n) ordered.Insert_After(refinery,Random_Pick(refinery_position,ordered.Count()-1));
            }
            break;
        }
        ++refinery_position;
    }
    DynamicVectorClass<BuildingTypeClass const *> final_queue;
    final_queue.Add(ordered[0]); final_queue.Add(ordered[1]); final_queue.Add(ordered[2]);
    for (i=3;i<ordered.Count();++i) final_queue.Add(ordered[i]);
    int defenses=soviet ? Rules->SovietBaseDefenseCounts[unknown_c8] : Rules->AlliedBaseDefenseCounts[unknown_c8];
    for (;defenses>0;--defenses) final_queue.Insert_After((BuildingTypeClass const *)-1,Random_Pick(3,final_queue.Count()-1));
    for (i=0;i<final_queue.Count();++i) {
        BuildingTypeClass const *type=final_queue[i];
        if ((int)type<0 && (int)type>=-4) unknown_55f0.Nodes.Add(BaseNodeClass((int)type,Cell(0,0),false,0));
        else unknown_55f0.Nodes.Add(BaseNodeClass(type->ArrayIndex,Cell(0,0),false,0));
    }
}
