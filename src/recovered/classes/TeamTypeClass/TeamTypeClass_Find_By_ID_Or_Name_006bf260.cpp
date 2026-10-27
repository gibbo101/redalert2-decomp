// TeamTypeClass *TeamTypeClass::Find_By_ID_Or_Name(char const *name) (0x006BF260)
// The first team type whose ID or Name matches name (case-insensitive).
#include "shared/team_type.hpp"

TeamTypeClass *__fastcall TeamTypeClass::Find_By_ID_Or_Name(char const *name)
{
    if (name != 0) {
        for (int index = 0; index < TeamTypes.Count(); index++) {
            if (_stricmp(name, TeamTypes[index]->ID) == 0 || _stricmp(name, TeamTypes[index]->Name) == 0) {
                return TeamTypes[index];
            }
        }
    }
    return 0;
}
