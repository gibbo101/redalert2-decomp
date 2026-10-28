// bool TActionClass::unknown_func_6b1f10(...) (0x006B1F10)
// Enables every trigger whose type is the one at +0x50 and is enabled for
// the scenario's difficulty (as 0x006B1F90 disables them); always true.
#include "shared/taction.hpp"
#include "shared/trigger.hpp"
#include "shared/trigger_type.hpp"
#include "shared/id_source.hpp"

bool TActionClass::unknown_func_6b1f10(HouseClass *house, ObjectClass *object, TriggerClass *trigger, Cell *cell)
{
    if (unknown_50 != 0) {
        for (int index = 0; index < unknown_TriggerClass_list_00a40aa0.Count(); index++) {
            TriggerTypeClass *type = unknown_TriggerClass_list_00a40aa0[index]->Class;
            if ((AbstractClass *)type == unknown_50) {
                if ((unknown_id_source_a3d290->Difficulty != 0 || type->IsEasy)
                        && (unknown_id_source_a3d290->Difficulty != 1 || type->IsNormal)
                        && (unknown_id_source_a3d290->Difficulty != 2 || type->IsHard)) {
                    unknown_TriggerClass_list_00a40aa0[index]->Enable();
                }
            }
        }
    }
    return true;
}
