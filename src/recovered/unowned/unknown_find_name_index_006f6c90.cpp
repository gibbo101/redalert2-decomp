// int __fastcall unknown_find_name_index(UnknownNameList_006f6c90 const &names, char const *name) -- 0x006F6C90
// Purpose: the index of name (exact, strcmp) in a list of names (a
// DynamicVectorClass: elements at +0x04, count at +0x10); -1 when absent.
// Assumptions: the list's owner is unidentified.
#include "shared/crt_string.hpp"

struct UnknownNameList_006f6c90 {
    void *vtable_00;
    char const **Vector;                    // +0x04
    int VectorMax;
    int unknown_0c;
    int ActiveCount;                        // +0x10
};

int __fastcall unknown_find_name_index(UnknownNameList_006f6c90 const &names, char const *name)
{
    for (int index = 0; index < names.ActiveCount; index++) {
        if (strcmp(name, names.Vector[index]) == 0) {
            return index;
        }
    }
    return -1;
}
