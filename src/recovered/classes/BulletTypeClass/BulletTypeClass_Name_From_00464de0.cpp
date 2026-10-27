// char const *__fastcall BulletTypeClass::Name_From(int index) (0x00464DE0)
#include "shared/bullet_type.hpp"

char const *__fastcall BulletTypeClass::Name_From(int index)
{
    if ((unsigned)index < (unsigned)BulletTypes.Count()) {
        return BulletTypes[index]->ID;
    }
    return 0;
}
