// WeaponTypeClass *__fastcall WeaponTypeClass::Find_Or_Make(char const *name) (0x00733EA0)
// The named weapon type, created when missing; 0 for "<none>" and "none".
#include "shared/weapon_type.hpp"

WeaponTypeClass *__fastcall WeaponTypeClass::Find_Or_Make(char const *name)
{
    if (!_stricmp("<none>", name) || !_stricmp("none", name)) {
        return 0;
    }
    for (int index = 0; index < unknown_WeaponTypeClass_list_00839b90.Count(); index++) {
        if (!_stricmp(unknown_WeaponTypeClass_list_00839b90[index]->ID, name)) {
            return unknown_WeaponTypeClass_list_00839b90[index];
        }
    }
    return new WeaponTypeClass(name);
}
