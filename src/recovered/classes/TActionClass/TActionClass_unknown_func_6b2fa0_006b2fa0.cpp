// bool TActionClass::unknown_func_6b2fa0(...) (0x006B2FA0)
// Runs BuildingClass::unknown_452f50(0) on the first living, active building whose tag has the action's trigger attached; true when one was found.
#include "shared/taction.hpp"
#include "shared/building.hpp"
#include "shared/tag.hpp"
// @ref ?unknown_BuildingClass_list_00a40af8@@3V?$DynamicVectorClass@PAVBuildingClass@@@@A=00a40af8
// @ref ?Is_Trigger_Attached@TagClass@@QBE_NPAVTriggerClass@@@Z=006b3dd0
// @ref ?unknown_452f50@BuildingClass@@QAEXH@Z=00452f50
extern DynamicVectorClass<BuildingClass *> unknown_BuildingClass_list_00a40af8;

bool TActionClass::unknown_func_6b2fa0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    bool handled = false;
    for (int index = 0; index < unknown_BuildingClass_list_00a40af8.Count(); index++) {
        BuildingClass *building = unknown_BuildingClass_list_00a40af8[index];
        if (building->unknown_7d && building->unknown_74 && !building->unknown_76 && building->unknown_34 != 0
            && building->unknown_34->Is_Trigger_Attached(trigger)) {
            building->unknown_452f50(0);
            handled = true;
            break;
        }
    }
    return handled;
}
