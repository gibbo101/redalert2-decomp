// TriggerClass *__fastcall TriggerClass::Find_Or_Make(TriggerTypeClass *type) (0x006ED8A0)
// The live trigger of a type, created when missing; 0 without a type.
#include "shared/object.hpp"

TriggerClass *__fastcall TriggerClass::Find_Or_Make(TriggerTypeClass *type)
{
    if (type != 0) {
        for (int index = 0; index < unknown_TriggerClass_list_00a40aa0.Count(); index++) {
            if (type == unknown_TriggerClass_list_00a40aa0[index]->Class) {
                return unknown_TriggerClass_list_00a40aa0[index];
            }
        }
        return new TriggerClass(type);
    }
    return 0;
}
