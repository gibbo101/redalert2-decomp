// int VoxClass::Find_Index(char const *name) (0x00716640): the index of the
// VoxClass of a name, -1 for none or a null name.
#include "shared/vox_class.hpp"
#include "shared/crt_string.hpp"
// @ref ?unknown_VoxClass_list_00ad0930@@3V?$DynamicVectorClass@PAVVoxClass@@@@A=00ad0930
// @ref __stricmp=00781f20

// The list search after the null test is a separate inline step: the original
// keeps the null test's -1 return before the search saves esi (one function
// body merges both -1 returns and saves esi at entry).
static inline int Index_Of_Name(char const *name)
{
    for (int index = 0; index < unknown_VoxClass_list_00ad0930.Count(); index++) {
        if (_stricmp(name, unknown_VoxClass_list_00ad0930[index]->Name) == 0) {
            return index;
        }
    }
    return -1;
}

int __fastcall VoxClass::Find_Index(char const *name)
{
    if (name == 0) {
        return -1;
    }
    return Index_Of_Name(name);
}
