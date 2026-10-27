// bool TActionClass::unknown_func_6b1f90(house, object, trigger, cell) (0x006B1F90)
// Disables every trigger whose type is the one at +0x50; always true.
#include "shared/taction.hpp"
#include "shared/trigger.hpp"
// @ref ?Disable@TriggerClass@@QAEXXZ=006edb70
// @ref ?unknown_TriggerClass_list_00a40aa0@@3V?$DynamicVectorClass@PAVTriggerClass@@@@A=00a40aa0

bool TActionClass::unknown_func_6b1f90(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (unknown_50 != 0) {
        for (int index = 0; index < unknown_TriggerClass_list_00a40aa0.Count(); index++) {
            if ((AbstractClass *)unknown_TriggerClass_list_00a40aa0[index]->Class == unknown_50) {
                unknown_TriggerClass_list_00a40aa0[index]->Disable();
            }
        }
    }
    return true;
}
