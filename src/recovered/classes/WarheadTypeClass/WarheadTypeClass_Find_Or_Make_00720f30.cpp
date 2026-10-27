// WarheadTypeClass *__fastcall WarheadTypeClass::Find_Or_Make(char const *name) (0x00720F30)
// The named warhead type, created when missing; 0 for "<none>" and "none".
#include "shared/warhead_type.hpp"

WarheadTypeClass *__fastcall WarheadTypeClass::Find_Or_Make(char const *name)
{
    if (!_stricmp("<none>", name) || !_stricmp("none", name)) {
        return 0;
    }
    for (int index = 0; index < unknown_WarheadTypeClass_list_00839b00.Count(); index++) {
        if (!_stricmp(unknown_WarheadTypeClass_list_00839b00[index]->ID, name)) {
            return unknown_WarheadTypeClass_list_00839b00[index];
        }
    }
    return new WarheadTypeClass(name);
}
