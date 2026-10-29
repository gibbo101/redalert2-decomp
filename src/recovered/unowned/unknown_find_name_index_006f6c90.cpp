// int __fastcall unknown_find_name_index(DynamicVectorClass<char const *> const &names, char const *name) -- 0x006F6C90
// Purpose: the index of name (exact, strcmp) in a list of names; -1 when absent.
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#define VECTOR_IMPLEMENT_DYNAMIC_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/crt_string.hpp"

int __fastcall unknown_find_name_index(DynamicVectorClass<char const *> const &names, char const *name)
{
    for (int index = 0; index < names.Count(); index++) {
        if (strcmp(name, names[index]) == 0) {
            return index;
        }
    }
    return -1;
}
