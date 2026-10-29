// bool TActionClass::unknown_spotlight_behavior_6b1d80(...) (0x006B1D80)
// Sets spotlight behavior Data on every living, active spotlight building whose tag has the trigger attached; true when any.
#include "shared/taction.hpp"
#include "shared/building.hpp"
#include "shared/building_light.hpp"
#include "shared/tag.hpp"
// @ref ?unknown_BuildingClass_list_00a40af8@@3V?$DynamicVectorClass@PAVBuildingClass@@@@A=00a40af8
// @ref ?Is_Trigger_Attached@TagClass@@QBE_NPAVTriggerClass@@@Z=006b3dd0
extern DynamicVectorClass<BuildingClass *> unknown_BuildingClass_list_00a40af8;

bool TActionClass::unknown_spotlight_behavior_6b1d80(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    bool handled = false;
    for (int index = 0; index < unknown_BuildingClass_list_00a40af8.Count(); index++) {
        BuildingClass *building = unknown_BuildingClass_list_00a40af8[index];
        if (building->Strength > 0 && building->unknown_7d && building->unknown_74 && !building->unknown_76
            && building->Type->HasSpotlight && building->unknown_4d4 != 0
            && building->unknown_34 != 0 && building->unknown_34->Is_Trigger_Attached(trigger)) {
            static_cast<BuildingLightClass *>(building->unknown_4d4)->Set_Behavior(Data);
            handled = true;
        }
    }
    return handled;
}
