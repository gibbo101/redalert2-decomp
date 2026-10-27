// void BulletClass::Construct(...) (0x0045F4F0)
// Sets up a new bullet; the inherited color comes from the owner's house
// when the type asks for it.
#include "shared/bullet.hpp"

void BulletClass::Construct(BulletTypeClass *type, AbstractClass *target, TechnoClass *owner,
                            int damage, WarheadTypeClass *warhead, int speed, bool bright)
{
    Type = type;
    Target = target;
    Speed = speed;
    WH = warhead;
    Bright = bright;
    Strength = damage;
    Owner = owner;
    AnimFrame = 0;
    AnimRateCounter = Type_View(type)->unknown_2c6;
    if (Type_View(type)->unknown_279 && owner != 0) {
        InheritedColor = Techno_View(owner)->House->unknown_15f40;
    } else {
        InheritedColor = -1;
    }
    DamageMultiplier = 0x100;
    NextAnim = 0;
    SpawnNextAnim = false;
}
