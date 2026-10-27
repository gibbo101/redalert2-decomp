// BulletTypeClass *__fastcall BulletTypeClass::Find_Or_Make(char const *name) (0x004650A0)
// The named bullet type, created when missing; 0 for "<none>" and "none".
#include "shared/bullet_type.hpp"

BulletTypeClass *__fastcall BulletTypeClass::Find_Or_Make(char const *name)
{
    if (!_stricmp("<none>", name) || !_stricmp("none", name)) {
        return 0;
    }
    for (int index = 0; index < BulletTypes.Count(); index++) {
        if (!_stricmp(BulletTypes[index]->ID, name)) {
            return BulletTypes[index];
        }
    }
    return new BulletTypeClass(name);
}
