// void BulletTypeClass::Detach(AbstractClass *target, bool all) (0x00465130)
#include "shared/bullet_type.hpp"

void BulletTypeClass::Detach(AbstractClass *target, bool all)
{
    if (target == (AbstractClass *)Trailer) {
        Trailer = 0;
    }
}
