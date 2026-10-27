// ScriptTypeClass *ScriptTypeClass::Find_Or_Make(char const *name) (0x00668F70)
// The script type with this ID, created when missing; null for "<none>"
// and "none".
#include "shared/script.hpp"
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??2@YAPAXI@Z=00782017

ScriptTypeClass *__fastcall ScriptTypeClass::Find_Or_Make(char const *name)
{
    if (_stricmp("<none>", name) == 0 || _stricmp("none", name) == 0) {
        return 0;
    }
    for (int index = 0; index < ScriptTypes.Count(); index++) {
        if (_stricmp(ScriptTypes[index]->ID, name) == 0) {
            return ScriptTypes[index];
        }
    }
    return new ScriptTypeClass(name);
}
