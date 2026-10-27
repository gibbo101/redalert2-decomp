// BulletTypeClass::BulletTypeClass(char const *ini_name) (0x004644E0)
// The projectile defaults (shadowed, rotating, anti-ground; one cluster,
// elasticity 0.75, acceleration and spawn delay 3), the object-type flags a
// projectile overrides, a new ID, and both type lists.
#include "shared/bullet_type.hpp"
// @ref ??0ObjectTypeClass@@QAE@PBD@Z=005d57f0
// @ref ?Create_ID@AbstractClass@@UAGXXZ=0040ffd0
// @ref ?BulletTypes@@3V?$DynamicVectorClass@PAVBulletTypeClass@@@@A=00a35cf0
// @ref ?unknown_objects_ac0cb0@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0cb0

BulletTypeClass::BulletTypeClass(char const *ini_name) :
    ObjectTypeClass(ini_name),
    Airburst(false),
    Floater(false),
    SubjectToCliffs(false),
    SubjectToElevation(false),
    SubjectToWalls(false),
    VeryHigh(false),
    Shadow(true),
    Arcing(false),
    Dropping(false),
    Level(false),
    Inviso(false),
    Proximity(false),
    Ranged(false),
    Rotates(true),
    Inaccurate(false),
    FlakScatter(false),
    AA(false),
    AG(true),
    Degenerates(false),
    Bouncy(false),
    AnimPalette(false),
    FirersPalette(false),
    Cluster(1),
    AirburstWeapon(0),
    ShrapnelWeapon(0),
    ShrapnelCount(0),
    DetonationAltitude(0),
    Vertical(false),
    Elasticity(0.75),
    Acceleration(3),
    Color(0),
    Trailer(0),
    ROT(0),
    CourseLockDuration(0),
    SpawnDelay(3),
    unknown_2b8(0),
    Scalable(false),
    Arm(0),
    AnimLow(0),
    AnimHigh(0),
    AnimRate(0),
    Flat(false)
{
    Create_ID();
    unknown_204 = true;
    unknown_1ff = true;
    unknown_200 = false;
    unknown_201 = false;
    unknown_202 = true;
    unknown_203 = true;
    unknown_205 = false;
    BulletTypes.Add(this);
    unknown_objects_ac0cb0.Add(this);
}
