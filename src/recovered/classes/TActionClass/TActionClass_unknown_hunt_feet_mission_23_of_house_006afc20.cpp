// bool TActionClass::unknown_hunt_feet_mission_23_of_house(...) (0x006AFC20)
// Sends every mission-23, living, active, non-limbo foot owned by the action's house to mission 5; always true.
#include "shared/taction.hpp"
#include "shared/foot.hpp"
// @ref ?unknown_FootClass_list_00865f38@@3V?$DynamicVectorClass@PAVFootClass@@@@A=00865f38
extern DynamicVectorClass<FootClass *> unknown_FootClass_list_00865f38;

bool TActionClass::unknown_hunt_feet_mission_23_of_house(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    for (int index = 0; index < unknown_FootClass_list_00865f38.Count(); index++) {
        FootClass *foot = unknown_FootClass_list_00865f38[index];
        if (foot->unknown_slot91() == 0x17 && foot->Strength > 0 && foot->unknown_7d && foot->unknown_74
            && !foot->unknown_76 && foot->House == house) {
            foot->unknown_slot116(5, false);
        }
    }
    return true;
}


