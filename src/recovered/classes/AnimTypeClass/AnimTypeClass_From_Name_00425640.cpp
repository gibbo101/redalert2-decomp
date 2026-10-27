// static int __fastcall AnimTypeClass::From_Name(char const *name) (0x00425640)
// Index of the type with this ID (case-insensitive), or -1.
#include "shared/anim_type.hpp"
// @ref __stricmp=00781f20

int __fastcall AnimTypeClass::From_Name(char const *name)
{
    if (name != 0) {
        for (int index = 0; index < AnimTypes.Count(); index++) {
            if (_stricmp(AnimTypes[index]->ID, name) == 0) {
                return index;
            }
        }
    }
    return -1;
}
