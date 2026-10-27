// WarheadTypeClass *__fastcall WarheadTypeClass::From_Name(char const *name) (0x00721020)
#include "shared/warhead_type.hpp"

WarheadTypeClass *__fastcall WarheadTypeClass::From_Name(char const *name)
{
    for (int index = 0; index < unknown_WarheadTypeClass_list_00839b00.Count(); index++) {
        if (!_stricmp(unknown_WarheadTypeClass_list_00839b00[index]->ID, name)) {
            return unknown_WarheadTypeClass_list_00839b00[index];
        }
    }
    return 0;
}
