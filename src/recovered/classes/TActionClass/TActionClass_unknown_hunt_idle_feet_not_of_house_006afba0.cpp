// bool TActionClass::unknown_hunt_idle_feet_not_of_house(...) (0x006AFBA0)
// Sends every idle (mission 0), living, active, non-limbo foot not owned by the action's house to mission 5; always true.
#include "shared/taction.hpp"
#include "shared/foot.hpp"
// @ref ?unknown_FootClass_list_00865f38@@3V?$DynamicVectorClass@PAVFootClass@@@@A=00865f38
extern DynamicVectorClass<FootClass *> unknown_FootClass_list_00865f38;

bool TActionClass::unknown_hunt_idle_feet_not_of_house(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    for (int index = 0; index < unknown_FootClass_list_00865f38.Count(); index++) {
        FootClass *foot = unknown_FootClass_list_00865f38[index];
        if (foot->unknown_slot91() == 0 && foot->Strength > 0 && foot->unknown_7d && foot->unknown_74
            && !foot->unknown_76 && house != foot->House) {
            foot->unknown_slot116(5, false);
        }
    }
    return true;
}
