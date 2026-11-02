// bool TActionClass::unknown_func_6b1e20(...) (0x006B1E20)
// Deletes every trigger whose type is the one at +0x50 (the count is read
// once; the index steps back after each deletion); always true.
#include "shared/taction.hpp"
#include "shared/trigger.hpp"

bool TActionClass::unknown_func_6b1e20(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (unknown_50 != 0) {
        int count = unknown_TriggerClass_list_00a40aa0.Count();
        for (int index = 0; index < count; index++) {
            if (unknown_TriggerClass_list_00a40aa0[index]->Class == (TriggerTypeClass *)unknown_50) {
                delete unknown_TriggerClass_list_00a40aa0[index];
                index--;
            }
        }
    }
    return true;
}


