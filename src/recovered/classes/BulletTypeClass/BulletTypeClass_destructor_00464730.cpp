// BulletTypeClass::~BulletTypeClass() (0x00464730)
#include "shared/bullet_type.hpp"

BulletTypeClass::~BulletTypeClass()
{
    Unknown_006ECB90((ObjectClass *)this, true);
    unknown_objects_ac0cb0.Delete((ObjectClass *)this);
    BulletTypes.Delete(this);
}
