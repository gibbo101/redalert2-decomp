// static SmudgeTypeClass *__fastcall SmudgeTypeClass::Find_Or_Make(char const *name) (0x006883D0)
// The type with this ID, else a new one; null for "<none>" and "none".
#include "shared/smudge_type.hpp"
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec
// @ref ??2@YAPAXI@Z=00782017

SmudgeTypeClass *__fastcall SmudgeTypeClass::Find_Or_Make(char const *name)
{
    if (_stricmp("<none>", name) == 0 || _stricmp("none", name) == 0) {
        return 0;
    }
    for (int index = 0; index < SmudgeTypes.Count(); index++) {
        if (_stricmp(SmudgeTypes[index]->ID, name) == 0) {
            return SmudgeTypes[index];
        }
    }
    return new SmudgeTypeClass(name);
}
