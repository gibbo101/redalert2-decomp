// TeamTypeClass *TeamTypeClass::Find_Or_Make(char const *name) (0x006BFB10)
// The team type with this ID, created when missing; null for "<none>" and
// "none".
#include "shared/team_type.hpp"
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??2@YAPAXI@Z=00782017

TeamTypeClass *__fastcall TeamTypeClass::Find_Or_Make(char const *name)
{
    if (_stricmp("<none>", name) == 0 || _stricmp("none", name) == 0) {
        return 0;
    }
    for (int index = 0; index < TeamTypes.Count(); index++) {
        if (_stricmp(TeamTypes[index]->ID, name) == 0) {
            return TeamTypes[index];
        }
    }
    return new TeamTypeClass(name);
}
