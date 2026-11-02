// char const *unknown_warhead_name_0040f3a0(int index) (0x0040F3A0)
// ID of the warhead type at this index of the unit's list 0x00839B00, or null.
// No direct callers.
#include "shared/warhead_type.hpp"

char const *__fastcall unknown_warhead_name_0040f3a0(int index)
{
    if (index != -1 && (unsigned)index < (unsigned)unknown_WarheadTypeClass_list_00839b00.Count()) {
        return unknown_WarheadTypeClass_list_00839b00[index]->ID;
    }
    return 0;
}
