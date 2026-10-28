// static int __fastcall SmudgeTypeClass::From_Name(char const *name) (0x00687F60)
// Index of the type with this ID (case-insensitive), or -1.
#include "shared/smudge_type.hpp"
// @ref __stricmp=00781f20

int __fastcall SmudgeTypeClass::From_Name(char const *name)
{
    if (name != 0) {
        for (int index = 0; index < SmudgeTypes.Count(); index++) {
            if (_stricmp(SmudgeTypes[index]->ID, name) == 0) {
                return index;
            }
        }
    }
    return -1;
}
