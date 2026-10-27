// static AnimTypeClass *__fastcall AnimTypeClass::Find_Or_Make(char const *name) (0x004264A0)
// The type with this ID, else a new one; null for "<none>" and "none".
#include "shared/anim_type.hpp"
// @ref ??2@YAPAXI@Z=00782017

AnimTypeClass *__fastcall AnimTypeClass::Find_Or_Make(char const *name)
{
    if (_stricmp("<none>", name) == 0 || _stricmp("none", name) == 0) {
        return 0;
    }
    for (int index = 0; index < AnimTypes.Count(); index++) {
        if (_stricmp(AnimTypes[index]->ID, name) == 0) {
            return AnimTypes[index];
        }
    }
    return new AnimTypeClass(name);
}
