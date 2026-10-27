// static char const *__fastcall AnimTypeClass::Name_From(int index) (0x00425620)
// The ID of the type at an index (the original's bound check admits Count).
#include "shared/anim_type.hpp"
// @ref ?unknown_string_83c55c@@3PADA=0083c55c

char const *__fastcall AnimTypeClass::Name_From(int index)
{
    if ((unsigned)index > (unsigned)AnimTypes.Count()) {
        return unknown_string_83c55c;
    }
    return AnimTypes[index]->ID;
}
