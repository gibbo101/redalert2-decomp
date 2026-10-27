// BulletClass *__fastcall Create_Bullet(...) (0x00463990)
#include "shared/bullet.hpp"

BulletClass *__fastcall Create_Bullet(BulletTypeClass *type, AbstractClass *target, TechnoClass *owner,
                                      int damage, WarheadTypeClass *warhead, int speed, bool bright)
{
    void *object = 0;
    if (FAILED(CoCreateInstance(CLSID_BulletClass, 0, 7, IID_IUnknown_7afce0, &object))) {
        return 0;
    }
    BulletClass *bullet = (BulletClass *)object;
    bullet->Construct(type, target, owner, damage, warhead, speed, bright);
    return bullet;
}
