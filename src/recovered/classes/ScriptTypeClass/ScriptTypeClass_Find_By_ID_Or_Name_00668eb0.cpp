// ScriptTypeClass *ScriptTypeClass::Find_By_ID_Or_Name(char const *name) (0x00668EB0)
// The first script type whose ID or Name matches name (case-insensitive).
#include "shared/script.hpp"

ScriptTypeClass *__fastcall ScriptTypeClass::Find_By_ID_Or_Name(char const *name)
{
    if (name != 0) {
        for (int index = 0; index < ScriptTypes.Count(); index++) {
            if (_stricmp(name, ScriptTypes[index]->ID) == 0 || _stricmp(name, ScriptTypes[index]->Name) == 0) {
                return ScriptTypes[index];
            }
        }
    }
    return 0;
}
