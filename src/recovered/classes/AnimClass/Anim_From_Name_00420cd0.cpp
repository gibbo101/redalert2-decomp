// int __fastcall Anim_From_Name(char const *name) (0x00420CD0)
// Index in AnimTypes of the type with this ID; -1 for null or "<none>".
#include "shared/anim.hpp"

int __fastcall Anim_From_Name(char const *name)
{
    if (name != 0 && _stricmp(name, "<none>") != 0) {
        for (int index = 0; index < AnimTypes.Count(); index++) {
            if (_stricmp(AnimTypes[index]->ID, name) == 0) {
                return index;
            }
        }
    }
    return -1;
}
