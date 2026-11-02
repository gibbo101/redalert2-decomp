// bool TActionClass::unknown_buildings_with_tag_power_down(...) (0x006B0280)
// Runs BuildingClass::unknown_44d530 on every living, active building flagged at +0x530 whose tag has the action's trigger attached; true when any was handled.
#include "shared/taction.hpp"
#include "shared/building.hpp"
#include "shared/tag.hpp"
// @ref ?unknown_BuildingClass_list_00a40af8@@3V?$DynamicVectorClass@PAVBuildingClass@@@@A=00a40af8
// @ref ?Is_Trigger_Attached@TagClass@@QBE_NPAVTriggerClass@@@Z=006b3dd0
// @ref ?unknown_44d530@BuildingClass@@QAEXXZ=0044d530
extern DynamicVectorClass<BuildingClass *> unknown_BuildingClass_list_00a40af8;

bool TActionClass::unknown_buildings_with_tag_power_down(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    bool handled = false;
    for (int index = 0; index < unknown_BuildingClass_list_00a40af8.Count(); index++) {
        BuildingClass *building = unknown_BuildingClass_list_00a40af8[index];
        if (building->unknown_7d && building->unknown_74 && !building->unknown_76 && building->unknown_34 != 0
            && building->unknown_34->Is_Trigger_Attached(trigger) && building->unknown_530) {
            building->unknown_44d530();
            handled = true;
        }
    }
    return handled;
}


