// bool TActionClass::unknown_buildings_with_tag_slot98(...) (0x006B01A0)
// Calls ObjectClass slot 98 (1) on every living, active building whose tag has the action's trigger attached; true when any was handled.
#include "shared/taction.hpp"
#include "shared/building.hpp"
#include "shared/tag.hpp"
// @ref ?unknown_BuildingClass_list_00a40af8@@3V?$DynamicVectorClass@PAVBuildingClass@@@@A=00a40af8
// @ref ?Is_Trigger_Attached@TagClass@@QBE_NPAVTriggerClass@@@Z=006b3dd0
extern DynamicVectorClass<BuildingClass *> unknown_BuildingClass_list_00a40af8;

bool TActionClass::unknown_buildings_with_tag_slot98(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    bool handled = false;
    for (int index = 0; index < unknown_BuildingClass_list_00a40af8.Count(); index++) {
        BuildingClass *building = unknown_BuildingClass_list_00a40af8[index];
        if (building->unknown_7d && building->unknown_74 && !building->unknown_76 && building->unknown_34 != 0
            && building->unknown_34->Is_Trigger_Attached(trigger)) {
            building->unknown_slot98(1);
            handled = true;
        }
    }
    return handled;
}


