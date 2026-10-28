// bool TActionClass::unknown_func_6b1ec0(house, object, trigger, cell) (0x006B1EC0)
// Springs (forced, no object) every trigger whose type is the one at +0x50; always true.
#include "shared/taction.hpp"
#include "shared/trigger.hpp"
// @ref ?Fire_Actions@TriggerClass@@QAE_NPAVObjectClass@@VCell@@@Z=006ed830
// @ref ?unknown_cell_abfdb0@@3VCell@@A=00abfdb0
extern Cell unknown_cell_abfdb0;   // 0x00ABFDB0
// @ref ?unknown_TriggerClass_list_00a40aa0@@3V?$DynamicVectorClass@PAVTriggerClass@@@@A=00a40aa0

bool TActionClass::unknown_func_6b1ec0(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (unknown_50 != 0) {
        for (int index = 0; index < unknown_TriggerClass_list_00a40aa0.Count(); index++) {
            if ((AbstractClass *)unknown_TriggerClass_list_00a40aa0[index]->Class == unknown_50) {
                unknown_TriggerClass_list_00a40aa0[index]->Fire_Actions(0, unknown_cell_abfdb0);
            }
        }
    }
    return true;
}
