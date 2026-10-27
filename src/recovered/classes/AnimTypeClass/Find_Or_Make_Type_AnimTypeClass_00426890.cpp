// AnimTypeClass *__fastcall Find_Or_Make_Type(char const *name, TypeList<AnimTypeClass *> &list) (0x00426890)
// The type with this ID in a list, else a new one; null for "<none>" and
// "none". Read_INI calls it for Next and Spawns (the other type keys expand
// AnimTypeClass::Find_Or_Make inline). Name hypothesis.
#include "shared/anim_type.hpp"

#pragma auto_inline(off)
AnimTypeClass *__fastcall Find_Or_Make_Type(char const *name, TypeList<AnimTypeClass *> &list)
{
    if (_stricmp("<none>", name) == 0 || _stricmp("none", name) == 0) {
        return 0;
    }
    for (int index = 0; index < list.Count(); index++) {
        if (_stricmp(list[index]->ID, name) == 0) {
            return list[index];
        }
    }
    return new AnimTypeClass(name);
}
#pragma auto_inline(on)
