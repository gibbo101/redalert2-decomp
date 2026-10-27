// bool TActionClass::unknown_infantry_with_tag_slot294(...) (0x006B0210)
// Calls InfantryClass slot 294 on every living, active infantry whose tag has the action's trigger attached; true when any was handled.
#include "shared/taction.hpp"
#include "shared/infantry.hpp"
#include "shared/tag.hpp"
// @ref ?Infantry@@3V?$DynamicVectorClass@PAVInfantryClass@@@@A=00a35e48
// @ref ?Is_Trigger_Attached@TagClass@@QBE_NPAVTriggerClass@@@Z=006b3dd0
extern DynamicVectorClass<InfantryClass *> Infantry;

bool TActionClass::unknown_infantry_with_tag_slot294(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    bool handled = false;
    for (int index = 0; index < Infantry.Count(); index++) {
        InfantryClass *infantry = Infantry[index];
        if (infantry->unknown_7d && infantry->unknown_74 && !infantry->unknown_76 && infantry->unknown_34 != 0
            && infantry->unknown_34->Is_Trigger_Attached(trigger)) {
            infantry->unknown_slot294();
            handled = true;
        }
    }
    return handled;
}
