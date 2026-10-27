// BulletClass::BulletClass() (0x0045F3B0)
// An empty bullet registered in Bullets.
#include "shared/bullet.hpp"

BulletClass::BulletClass() :
    Type(0),
    Owner(0),
    unknown_a0(false),
    Bright(false),
    unknown_e8(0),
    unknown_ec(true),
    unknown_ed(true),
    unknown_f0(0),
    Target(0),
    Speed(0),
    InheritedColor(-1),
    unknown_100(0),
    unknown_108(0),
    WH(0),
    AnimFrame(0),
    AnimRateCounter(0),
    WeaponType(0),
    LastMapCoords(-1, -1),
    NextAnim(0),
    SpawnNextAnim(false)
{
    Create_ID();
    SourceCoords.X = 0;
    SourceCoords.Y = 0;
    SourceCoords.Z = 0;
    TargetCoords.X = 0;
    TargetCoords.Y = 0;
    TargetCoords.Z = 0;
    unknown_BulletClass_list_00a40ce8.Add(this);
}
