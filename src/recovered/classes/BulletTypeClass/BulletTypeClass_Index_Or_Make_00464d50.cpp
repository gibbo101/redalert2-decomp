// int __fastcall BulletTypeClass::Index_Or_Make(char const *name) (0x00464D50)
// The index of the named bullet type in BulletTypes, created when missing;
// -1 for "<none>".
#include "shared/bullet_type.hpp"

int __fastcall BulletTypeClass::Index_Or_Make(char const *name)
{
    if (_stricmp(name, "<none>") == 0) {
        return -1;
    }
    for (int index = 0; index < BulletTypes.Count(); index++) {
        if (_stricmp(name, BulletTypes[index]->ID) == 0) {
            return index;
        }
    }
    BulletTypeClass *type = new BulletTypeClass(name);
    return BulletTypes.ID(type);
}
