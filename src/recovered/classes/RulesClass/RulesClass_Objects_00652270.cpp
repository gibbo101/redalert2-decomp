// RulesClass::Objects (0x00652270)
// @ref ?Read_INI@MissionControlClass@@QAE_NAAVCCINIClass@@@Z=00594e30
// @ref ?unknown_func_45eaa0@BuildingTypeClass@@QAEXXZ=0045eaa0
// @ref ??8?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UBE_NABV0@@Z=00634c40
// @ref ??8?$VectorClass@USubzoneConnectionStruct@@@@UBE_NABV0@@Z=0040b070
// @ref ??_7?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@6B@=007a8824
// @ref ??_7?$VectorClass@USubzoneConnectionStruct@@@@6B@=0079a76c
// @ref ??_E?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UAEPAXI@Z=00635040
// @ref ??_E?$VectorClass@USubzoneConnectionStruct@@@@UAEPAXI@Z=0040b230
// @ref ??_G?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UAEPAXI@Z=00635040
// @ref ??_G?$VectorClass@USubzoneConnectionStruct@@@@UAEPAXI@Z=0040b230
// @ref ?Clear@?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UAEXXZ=00634da0
// @ref ?Clear@?$VectorClass@USubzoneConnectionStruct@@@@UAEXXZ=0040b1a0
// @ref ?Fetch@?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UBE?AU?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@H@Z=00634c10
// @ref ?Fetch@?$VectorClass@USubzoneConnectionStruct@@@@UBE?AUSubzoneConnectionStruct@@H@Z=0040b050
// @ref ?ID@?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UAEHABU?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@Z=00634dd0
// @ref ?ID@?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UAEHPBU?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@Z=00634e20
// @ref ?ID@?$VectorClass@USubzoneConnectionStruct@@@@UAEHABUSubzoneConnectionStruct@@@Z=0040b1d0
// @ref ?ID@?$VectorClass@USubzoneConnectionStruct@@@@UAEHPBUSubzoneConnectionStruct@@@Z=0040b210
// @ref ?Resize@?$VectorClass@U?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@@UAE_NHPBU?$HashObject@URadarTrackingStruct@@PAVTechnoClass@@@@@Z=00634ca0
// @ref ?Resize@?$VectorClass@USubzoneConnectionStruct@@@@UAE_NHPBUSubzoneConnectionStruct@@@Z=0040b0b0
// Each type reads its own rules section (the animations their art section),
// then the weapon and building types finish their setup, then each mission
// reads its section.
#include "shared/ccini_class.hpp"
#include "shared/rules.hpp"
#include "shared/house_type.hpp"
#include "shared/super_weapon_type.hpp"
#include "shared/anim_type.hpp"
#include "shared/building_type.hpp"
#include "shared/aircraft_type.hpp"
#include "shared/unit_type.hpp"
#include "shared/infantry_type.hpp"
#include "shared/weapon_type.hpp"
#include "shared/bullet_type.hpp"
#include "shared/warhead_type.hpp"
#include "shared/terrain_type.hpp"
#include "shared/smudge_type.hpp"
#include "shared/overlay_type.hpp"
#include "shared/particle_system.hpp"
#include "shared/voxel_anim_type.hpp"
#include "shared/mission.hpp"

bool RulesClass::Objects(CCINIClass &ini)
{
    int index;
    for (index = 0; index < HouseTypes.Count(); index++) {
        HouseTypes[index]->Read_INI(ini);
    }
    for (index = 0; index < SuperWeaponTypes.Count(); index++) {
        SuperWeaponTypes[index]->Read_INI(ini);
    }
    for (index = 0; index < AnimTypes.Count(); index++) {
        AnimTypes[index]->Read_INI(ArtINI);
    }
    for (index = 0; index < BuildingTypes.Count(); index++) {
        BuildingTypes[index]->Read_INI(ini);
    }
    for (index = 0; index < AircraftTypes.Count(); index++) {
        AircraftTypes[index]->Read_INI(ini);
    }
    for (index = 0; index < UnitTypes.Count(); index++) {
        UnitTypes[index]->Read_INI(ini);
    }
    for (index = 0; index < InfantryTypes.Count(); index++) {
        InfantryTypes[index]->Read_INI(ini);
    }
    for (index = 0; index < unknown_WeaponTypeClass_list_00839b90.Count(); index++) {
        unknown_WeaponTypeClass_list_00839b90[index]->Read_INI(ini);
    }
    for (index = 0; index < BulletTypes.Count(); index++) {
        BulletTypes[index]->Read_INI(ini);
    }
    for (index = 0; index < unknown_WarheadTypeClass_list_00839b00.Count(); index++) {
        unknown_WarheadTypeClass_list_00839b00[index]->Read_INI(ini);
    }
    for (index = 0; index < unknown_WeaponTypeClass_list_00839b90.Count(); index++) {
        unknown_WeaponTypeClass_list_00839b90[index]->unknown_func_7339c0();
    }
    for (index = 0; index < BuildingTypes.Count(); index++) {
        BuildingTypes[index]->unknown_func_45eaa0();
    }
    for (index = 0; index < TerrainTypes.Count(); index++) {
        TerrainTypes[index]->Read_INI(ini);
    }
    for (index = 0; index < SmudgeTypes.Count(); index++) {
        SmudgeTypes[index]->Read_INI(ini);
    }
    for (index = 0; index < OverlayTypes.Count(); index++) {
        OverlayTypes[index]->Read_INI(ini);
    }
    for (index = 0; index < ParticleTypes.Count(); index++) {
        ParticleTypes[index]->Read_INI(ini);
    }
    for (index = 0; index < ParticleSystemTypes.Count(); index++) {
        ParticleSystemTypes[index]->Read_INI(ini);
    }
    for (index = 0; index < VoxelAnimTypes.Count(); index++) {
        VoxelAnimTypes[index]->Read_INI(ini);
    }
    for (int mission = 0; mission < 30; mission++) {
        MissionControl[mission].Mission = mission;
        MissionControl[mission].Read_INI(ini);
    }
    return true;
}
