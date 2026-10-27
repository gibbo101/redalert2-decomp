// ScriptTypeClass *ScriptTypeClass::Find_By_Name(char const *name) (0x00668F20)
// The script type whose Name matches name (case-insensitive), or null.
#include "shared/script.hpp"

ScriptTypeClass *__fastcall ScriptTypeClass::Find_By_Name(char const *name)
{
    if (name != 0) {
        for (int index = 0; index < ScriptTypes.Count(); index++) {
            if (_stricmp(name, ScriptTypes[index]->Name) == 0) {
                return ScriptTypes[index];
            }
        }
    }
    return 0;
}
