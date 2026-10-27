// BulletClass::~BulletClass() (0x0045F590)
#include "shared/bullet.hpp"

BulletClass::~BulletClass()
{
    Unknown_006ECB90(this, true);
    if (SpawnNextAnim) {
        unknown_abstracts_ac0bf8.Delete(this);
    }
    if (unknown_flag_a40958) {
        ObjectClass::unknown_slot52();
    }
    Type = 0;
    Owner = 0;
    NextAnim = 0;
    unknown_BulletClass_list_00a40ce8.Delete(this);
}
